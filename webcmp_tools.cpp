#include "webcmp_tools.h"

#include <iostream>

size_t custom_curl_writefunc(char *data, size_t size, size_t nmemb, std::string *writerData)
{
    if (writerData == NULL)
        return 0;

    writerData->append(data, size * nmemb);

    return size * nmemb;
}

BrowserCurl::BrowserCurl()
{
    // CURL *curl_handle;

    curl_global_init(CURL_GLOBAL_ALL);

    /* init the curl session */
    curl_handle = curl_easy_init();

    /* no progress meter please */
    curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1L);

    CURLcode res;
    // std::string buffer;
    res = curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, &page);
    if (res != CURLE_OK)
    {
        error_msg = curl_easy_strerror(res);
        return;
    }

    /* send all data to this function  */
    res = curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, custom_curl_writefunc);
    if (res != CURLE_OK)
    {
        error_msg = curl_easy_strerror(res);
        return;
    }
}

BrowserCurl::~BrowserCurl()
{
    /* cleanup curl stuff */
    curl_easy_cleanup(curl_handle);
}

bool BrowserCurl::go(const std::string& url)
{
    CURLcode res;
    page.clear();
    page.reserve(1024*1024*50);
    error_msg.clear();

    /* set URL to get */
    res = curl_easy_setopt(curl_handle, CURLOPT_URL, url.c_str());
    if (res != CURLE_OK)
    {
        error_msg = curl_easy_strerror(res);
        return false;
    }

    /* get it! */
    res = curl_easy_perform(curl_handle);
    if (res != CURLE_OK)
    {
        error_msg = curl_easy_strerror(res);
        return false;
    }

    return true;
}

std::vector<std::tuple<int, int>> find_regex(const std::string &s, const std::regex &target_regex)
{
    std::vector<std::tuple<int, int>> v;
    v.reserve(10);

    std::smatch m;
    auto here = s.begin();
    auto end = s.end();
    
    while (std::regex_search(here, end, m, target_regex))
    {
        // Record the substr as {position, length}
        v.emplace_back(here - s.begin() + m.position(), m.length());

        here = m[0].second;
    }
    return v;
}
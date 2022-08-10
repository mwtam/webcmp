#include "webcmp_tools.h"

#include <iostream>
#include <algorithm>

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

std::vector<std::string_view> search_regex_str_v(const std::string &s, const std::regex &target_regex)
{
    std::vector<std::string_view> v;
    v.reserve(100);

    std::smatch m;
    auto here = s.begin();
    
    while (std::regex_search(here, s.end(), m, target_regex))
    {
        v.emplace_back(m[0].first, m[0].second);

        here = m[0].second;
    }
    return v;
}

void normalize_result(std::vector<std::string_view> &v)
{
    std::ranges::sort(v);
    const auto [first, last] = std::ranges::unique(v.begin(), v.end());
    v.erase(first, last);
}
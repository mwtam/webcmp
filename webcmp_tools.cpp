#include "webcmp_tools.h"
// #include <curl/curl.h>

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

std::string::size_type BrowserCurl::go(const std::string& url)
{
    if (!error_msg.empty())
    {
        return 0;
    }

    CURLcode res;
    page.clear();
    page.reserve(1024*1024*50);

    /* set URL to get */
    curl_easy_setopt(curl_handle, CURLOPT_URL, url.c_str());

    /* get it! */
    res = curl_easy_perform(curl_handle);

    if (res != CURLE_OK)
    {
        error_msg = curl_easy_strerror(res);
        return 0;
    }

    return page.length();
}


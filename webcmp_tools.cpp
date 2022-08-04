#include "webcmp_tools.h"
#include <curl/curl.h>


int write_data(char *data, size_t size, size_t nmemb,
                      std::string *writerData)
{
    if (writerData == NULL)
        return 0;

    writerData->append(data, size * nmemb);

    return size * nmemb;
}

std::string download_page(const std::string &url)
{
    // Example
    // - https://curl.se/libcurl/c/sepheaders.html
    //
    // My writer is more similar to
    // - https://curl.se/libcurl/c/htmltitle.html
    // for it writes to a string

    // TODO: Add error handling

    CURL *curl_handle;

    curl_global_init(CURL_GLOBAL_ALL);

    /* init the curl session */
    curl_handle = curl_easy_init();

    /* set URL to get */
    curl_easy_setopt(curl_handle, CURLOPT_URL, url);

    /* no progress meter please */
    curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1L);

    CURLcode code;
    std::string buffer;
    code = curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, &buffer);
    if (code != CURLE_OK)
    {
        return "+++";
    }
    /* send all data to this function  */
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_data);

    /* get it! */
    curl_easy_perform(curl_handle);

    /* cleanup curl stuff */
    curl_easy_cleanup(curl_handle);

    return buffer;
}

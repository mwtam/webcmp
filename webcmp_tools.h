#ifndef WEBCMP_TOOLS__H
#define WEBCMP_TOOLS__H

#include <string>
#include <curl/curl.h>

// Example
// - https://curl.se/libcurl/c/sepheaders.html
//
// My writer is more similar to
// - https://curl.se/libcurl/c/htmltitle.html
// for it writes to a string

// TODO: Add error handling
class BrowserCurl
{
public:
    BrowserCurl();
    virtual ~BrowserCurl();
    std::string::size_type go(const std::string& url);
    // std::string page;
    std::string page; // the page will be here
    std::string error_msg;

private:
    CURL *curl_handle;
};

#endif
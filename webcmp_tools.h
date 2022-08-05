#ifndef WEBCMP_TOOLS__H
#define WEBCMP_TOOLS__H

#include <string>
#include <curl/curl.h>

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
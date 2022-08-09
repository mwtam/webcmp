#ifndef WEBCMP_TOOLS__H
#define WEBCMP_TOOLS__H

#include <string>
#include <regex>
#include <vector>
#include <curl/curl.h>

class BrowserCurl
{
public:
    BrowserCurl();
    virtual ~BrowserCurl();
    bool go(const std::string &url);
    // std::string page;
    std::string page; // the page will be here
    std::string error_msg;

private:
    CURL *curl_handle;
};

std::vector<std::string> find_regex(const std::string &s, const std::regex &target_regex);

#endif
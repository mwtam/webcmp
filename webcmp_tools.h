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
    std::string page;
    std::string error_msg;

private:
    CURL *curl_handle;
};

// Search for target_regex in s
// Return a vector of string_view refers to s
// Hence
// 1. s must be a std::string, and
// 2. s must live when the returned vector is used
std::vector<std::string_view> find_regex(const std::string &s, const std::regex &target_regex);

#endif
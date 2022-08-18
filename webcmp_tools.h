#ifndef WEBCMP_TOOLS__H
#define WEBCMP_TOOLS__H

#include <string>
#include <regex>
#include <vector>
#include <boost/json.hpp>
#include <curl/curl.h>

// TODO: Better error handling
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
std::vector<std::string_view> search_regex_str_v(const std::string &s, const std::regex &target_regex);

// Trap the call to this function with char*
// Code will not compile if called this way.
void search_regex_str_v(const char *s, const std::regex &target_regex);

// Normalize the result vector in-place
void normalize_result(std::vector<std::string_view> &v);

void write_result(const std::string &filename, const std::vector<std::string_view> &v);

boost::json::value read_json(const std::string &work_file, boost::json::error_code &ec);

#endif
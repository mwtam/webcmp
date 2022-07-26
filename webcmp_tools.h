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
    long response_code;

private:
    CURL *curl_handle;
};

// Search for target_regex in s
// Return a vector of string_view refers to s
// Hence
// 1. s must be a std::string, and
// 2. s must live when the returned vector is used
std::vector<std::string_view> search_regex_str_v(const std::string_view &s, const std::regex &target_regex);

// Normalize the result vector in-place
void normalize_result(std::vector<std::string_view> &v);

std::string read_file(const std::string &filename);

void write_result(const std::string &filename, const std::vector<std::string_view> &v);
std::vector<std::string_view> to_result(const std::string &s);

boost::json::value read_json(const std::string &work_file, boost::json::error_code &ec);

#endif
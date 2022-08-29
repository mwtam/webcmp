#include "webcmp_tools.h"

#include <iostream>
#include <fstream>
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
    CURLcode res;

    res = curl_global_init(CURL_GLOBAL_ALL);
    if (res != CURLE_OK)
    {
        error_msg = curl_easy_strerror(res);
        return;
    }

    /* init the curl session */
    curl_handle = curl_easy_init();
    if (!curl_handle)
    {
        error_msg = "curl_easy_init() returns NULL";
        return;
    }

    /* no progress meter please */
    res = curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1L);
    if (res != CURLE_OK)
    {
        error_msg = curl_easy_strerror(res);
        return;
    }

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

bool BrowserCurl::go(const std::string &url)
{
    CURLcode res;
    page.clear();
    page.reserve(1024 * 1024 * 50);
    error_msg.clear();
    response_code = 0;

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

    curl_easy_getinfo(curl_handle, CURLINFO_RESPONSE_CODE, &response_code);
    if (response_code != 200)
    {
        error_msg = "Response: ";
        error_msg += std::to_string(response_code);
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

void write_result(const std::string &filename, const std::vector<std::string_view> &v)
{
    std::ofstream fout;
    fout.open(filename);
    for (auto &&l : v)
    {
        fout << l << "\n";
    }
}

std::string read_file(const std::string &filename)
{
    std::ifstream t(filename);
    std::stringstream buffer;
    buffer << t.rdbuf();
    return buffer.str();
}

std::vector<std::string_view> to_result(const std::string &s)
{
    std::vector<std::string_view> v;

    auto from = s.begin();
    auto to = s.begin();
    while (true)
    {
        while (*to != '\n' && to != s.end())
        {
            ++to;
        }

        v.emplace_back(from, to);

        if (to == s.end())
        {
            break;
        }

        from = to + 1;
        to = from;

        if (from == s.end())
        {
            // The last char is a '\n'
            break;
        }
    }

    return v;
}

boost::json::value read_json(const std::string &work_file, boost::json::error_code &ec)
{
    std::ifstream t(work_file);
    std::stringstream buffer;
    buffer << t.rdbuf();
    // std::cout << buffer.str() << "\n";

    boost::json::parse_options opt;
    opt.allow_comments = true;
    opt.allow_trailing_commas = true;

    return boost::json::parse(buffer.str(), ec, {}, opt);
}
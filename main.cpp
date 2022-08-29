#include <iostream>
#include <fstream>
#include <array>
#include <string>
#include <filesystem>
#include "webcmp_tools.h"

void work(const std::string &work_file)
{
    boost::json::error_code ec;
    auto jv = read_json(work_file, ec);

    if (ec)
    {
        std::cout << "Error when reading " << work_file << "\n";
        std::cout << "Error: " << ec << " " << ec.message() << "\n";
        return;
    }

    BrowserCurl b;
    if (b.error_msg != "")
    {
        std::cout << "Error in curl: " << b.error_msg << "\n";
        return;
    }

    for (auto &&[task_id, obj] : jv.as_object())
    {
        std::cout << "Working on: " << task_id << " - ";

        const auto URL = 0;
        const auto REGEX = 1;
        std::array<std::string, 2> m;
        for (auto &&[key, value] : obj.as_object())
        {
            if (key == "url")
            {
                m[URL] = value.get_string();
                continue;
            }
            if (key == "regex")
            {
                m[REGEX] = value.get_string();
                continue;
            }
            // Unknown key. Ignored.
        }
        const auto &url = m[URL];
        const auto &regex = m[REGEX];

        if (!b.go(url))
        {
            std::cout << "Error" << "\n";
            std::cout << "    " << url << "\n";
            std::cout << "    " << b.error_msg << "\n";
            continue;
        }

        std::string& s = b.page;

        auto v = search_regex_str_v(s, std::regex(regex));
        normalize_result(v);

        // Read the memory
        std::filesystem::path f{ task_id };
        if (!std::filesystem::exists(f))
        {
            std::cout << "New Entry"
                      << "\n";
            // New file
            write_result(task_id, v);
            continue;
        }
        // Result is a vector of string_view,
        // so need to keep the original string
        auto result_s = read_file(task_id);
        auto result_v = to_result(result_s);

        if (v == result_v)
        {
            std::cout << "Unchanged"
                      << "\n";
        }
        else
        {
            std::cout << "Changed"
                      << "\n";
            std::cout << "    " << url << "\n";
            write_result(task_id, v);
        }
    }
}

int main(int, char **)
{
    work("webcmp_work.json");
    return 0;
}

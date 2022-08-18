#include <iostream>
#include <fstream>
#include <array>
#include <string>
#include "webcmp_tools.h"

// TESTING
std::string temp_read_file()
{
    std::ifstream t("oracle_site.html");
    std::stringstream buffer;
    buffer << t.rdbuf();
    return buffer.str();
}
// TESTING

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

    for (auto &&[task_id, obj] : jv.as_object())
    {
        std::cout << "Working on: " << task_id << "\n";

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

        // TESTING
        // if (!b.go(url))
        // {
        //     std::cout << "Error when visiting " << url << "\n";
        //     std::cout << "Error: " << b.error_msg << "\n";
        //     return;
        // }

        // std::string& s = b.page;
        // TESTING

        // TESTING
        // Read the html from file instead of going to the site.
        auto s = temp_read_file();
        // TESTING

        auto v = search_regex_str_v(s, std::regex(regex));
        normalize_result(v);

        // TODO:
        // Compare the result with memory
        //     - if same, report "unchanged"
        //     - if different
        //         - move the old file away
        //         - save the new file
        //         - report "updated"
        write_result(task_id, v);
    }
}

int main(int, char **)
{
    work("webcmp_work.json");
    return 0;
}

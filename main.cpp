#include <iostream>
#include <vector>
#include "webcmp_tools.h"

int main(int, char **)
{
    read_json();
    return 0;
}

// int main(int, char **)
// {
//     std::cout << "Hello, world! From main\n";

//     std::vector v = {
//         "https://example.com",
//         "https://example.comxxx",
//     };

//     BrowserCurl b;

//     for (auto &&url : v)
//     {
//         std::cout << "Visiting: " << url << "\n";
//         if (b.go(url) > 0)
//         {
//             std::cout << b.page << "\n";
//         }
//         else
//         {
//             std::cout << "Something's wrong: " << b.error_msg << "\n";
//         }
//     }
// }

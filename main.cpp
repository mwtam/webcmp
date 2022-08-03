#include <iostream>
#include "webcmp_tools.h"

int main(int, char**) {
    std::cout << "Hello, world! From main\n";
    std::cout << download_page("https://example.com") << "\n";
}

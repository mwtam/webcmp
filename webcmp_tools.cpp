#include "webcmp_tools.h"
#include <curl/curl.h>

// Example
// - https://curl.se/libcurl/c/sepheaders.html
//
// My writer is more similar to
// - https://curl.se/libcurl/c/htmltitle.html
// for it writes to a string

std::string download_page(const std::string& url)
{
    return "Hello Page";
}
cmake_minimum_required(VERSION 3.0.0)
project(webcmp VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)

find_package(GTest REQUIRED)

add_executable(webcmp main.cpp webcmp_tools.cpp)
find_package(CURL REQUIRED) 
find_package( 
 Boost 1.80 REQUIRED 
 COMPONENTS json
 # At least need 1.75
 # Ubuntu has 1.74
 # Build 1.80 from source
 # See https://www.boost.org/doc/libs/1_80_0/more/getting_started/unix-variants.html
)
# include_directories(${CURL_INCLUDE_DIR})
# target_link_libraries(webcmp ${CURL_LIBRARIES})
target_link_libraries(
  webcmp 
  CURL::libcurl
  ${Boost_LIBRARIES}
)

target_compile_options(webcmp PRIVATE -Wall -Wextra -Wpedantic -Werror)

enable_testing()

include(GoogleTest)

add_executable(webcmp_test main_test.cpp webcmp_tools.cpp)

target_link_libraries(
  webcmp_test
  CURL::libcurl
  GTest::gtest_main
  ${Boost_LIBRARIES}
)

gtest_discover_tests(webcmp_test)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

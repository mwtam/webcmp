cmake_minimum_required(VERSION 3.0.0)
project(webcmp VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)

find_package(GTest REQUIRED)

add_executable(webcmp main.cpp webcmp_tools.cpp)
find_package(CURL REQUIRED) 
# include_directories(${CURL_INCLUDE_DIR})
# target_link_libraries(webcmp ${CURL_LIBRARIES})
target_link_libraries(webcmp CURL::libcurl)

enable_testing()

include(GoogleTest)

add_executable(webcmp_test main_test.cpp)

target_link_libraries(
  webcmp_test
  GTest::gtest_main
)

gtest_discover_tests(webcmp_test)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

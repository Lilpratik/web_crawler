cmake_minimum_required(VERSION 3.10)
project(WebCrawler)

set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(include)

# Add the executable
add_executable(web_crawler src/main.cpp src/crawler.cpp src/html_parser.cpp)

# Find and link required libraries
find_package(CURL REQUIRED)
target_link_libraries(web_crawler CURL::libcurl)

# Link the Gumbo library
find_library(GUMBO_LIB gumbo REQUIRED)
if (GUMBO_LIB)
    message(STATUS "Found Gumbo library at ${GUMBO_LIB}")
    target_link_libraries(web_crawler ${GUMBO_LIB})
else()
    message(FATAL_ERROR "Gumbo library not found. Please install it.")
endif()

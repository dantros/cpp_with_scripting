cmake_minimum_required(VERSION 3.20)
set(CMAKE_LEGACY_CYGWIN_WIN32 OFF)

project(cpp_console_app_project CXX)

add_subdirectory("third_party/whereami2cpp")

add_executable(cpp_console_app "source/main.cpp")
set_property(TARGET cpp_console_app PROPERTY CXX_STANDARD 20)
target_include_directories(cpp_console_app PRIVATE
    "third_party/argparse/include"
    "third_party/whereami2cpp/source"
    "third_party/spdlog/include"
    "third_party/json/include"
)
target_link_libraries(cpp_console_app PRIVATE whereami2cpp)

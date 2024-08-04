cmake_minimum_required(VERSION 3.20)
set(CMAKE_LEGACY_CYGWIN_WIN32 OFF)

project(cpp_with_scripting_project CXX)

add_subdirectory("third_party/whereami2cpp")
add_subdirectory("third_party/lua_cmake")

if (MSVC)
    add_compile_options(/bigobj)
else ()
    add_compile_options(-Wa,-mbig-obj)
endif ()

add_executable(demo_chaiscript "source/demo_chaiscript.cpp")
set_property(TARGET demo_chaiscript PROPERTY CXX_STANDARD 20)
target_include_directories(demo_chaiscript PRIVATE
    "third_party/ChaiScript/include"
)

add_executable(demo_lua "source/demo_lua.cpp")
set_property(TARGET demo_lua PROPERTY CXX_STANDARD 20)
target_include_directories(demo_lua PRIVATE
    "third_party/lua_cmake/lua-5.4.7/src"
)
target_link_libraries(demo_lua PRIVATE lua_static)

add_executable(demo_lua_sol "source/demo_lua_sol.cpp")
set_property(TARGET demo_lua_sol PROPERTY CXX_STANDARD 20)
target_include_directories(demo_lua_sol PRIVATE
    "third_party/lua_cmake/lua-5.4.7/src"
    "third_party/sol2"
)
target_link_libraries(demo_lua_sol PRIVATE lua_static)
# Lua was built with C++
target_compile_definitions(demo_lua_sol PRIVATE SOL_USING_CXX_LUA)
# Enabling sol safeties
target_compile_definitions(demo_lua_sol PRIVATE SOL_ALL_SAFETIES_ON)
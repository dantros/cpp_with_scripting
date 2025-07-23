cmake_minimum_required(VERSION 3.20)
set(CMAKE_LEGACY_CYGWIN_WIN32 OFF)

project(cpp_with_scripting_project CXX)

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

add_subdirectory("third_party/pocketpy")
add_executable(demo_pocketpy "source/demo_pocketpy.cpp")
set_property(TARGET demo_pocketpy PROPERTY CXX_STANDARD 20)
target_include_directories(demo_pocketpy PRIVATE
    "third_party/pocketpy/include"
)
target_link_libraries(demo_pocketpy PRIVATE pocketpy)

add_subdirectory("third_party/lua_sol_cmake")
add_executable(demo_lua_sol "source/demo_lua_sol.cpp")
set_property(TARGET demo_lua_sol PROPERTY CXX_STANDARD 20)
target_include_directories(demo_lua_sol PRIVATE
    ${LUA_SOL_INCLUDE}
)
target_link_libraries(demo_lua_sol PRIVATE lua_sol)

add_executable(loading_lua_file "source/loading_lua_file.cpp")
set_property(TARGET loading_lua_file PROPERTY CXX_STANDARD 20)
target_include_directories(loading_lua_file PRIVATE
    "third_party/argparse/include"
    ${LUA_SOL_INCLUDE}
)
target_link_libraries(loading_lua_file PRIVATE lua_sol)

# A limitation of CMake is the scope of the targets. We cannot use lua_static defined
# internally here via add_subdirectory("third_party/lua_cmake") and then defined again internally
# when calling add_subdirectory("third_party/lua_sol_cmake"), which it has the same dependency.
# A big real project can handle this by using FetchContent and carefully hand crafting each CMake.
# Since this is a basic teaching example, we are not doing that. This repo is managing third party
# dependencies via git submodule, so merging 2 "downloading dependencies systems" seems cumbersome,
# unnecesary and it will also require to modify these external libraries (lua_cmake and lua_sol_cmake).
# 
# If you are only interested in building directly the demo_lua example, you can uncomment the following
# lines, but you need to comment all lua+sol examples.
# ------ DEMO LUA STADNALONE
#
# option(LUA_CMAKE_BUILD_STATIC_LIB "" TRUE)
# option(LUA_CMAKE_BUILD_INTERPRETER "" FALSE)
# option(LUA_CMAKE_BUILD_COMPILER "" FALSE)
# add_subdirectory("third_party/lua_cmake")
# add_executable(demo_lua "source/demo_lua.cpp")
# set_property(TARGET demo_lua PROPERTY CXX_STANDARD 20)
# target_include_directories(demo_lua PRIVATE
#     "third_party/lua_cmake/lua-5.4.7/src"
# )
# target_link_libraries(demo_lua PRIVATE lua_static)
#
# ------ END OF DEMO LUA STADNALONE
#
# To avoid the mentioned CMake caveat, we are linking lua against lua_static built inside lua_sol.
# once again, this is only for illustration purposes, as a typical repository would not require to have
# lua and lua via sol active at the same time. And if it does, it just need to properly handcraft each
# static library using different names.
#
# Do note that we are not using add_subdirectory("third_party/lua_cmake"), so in a way ti can be removed
# from this repo, but we keep it here just to allow you to test the specific case of using only directly lua
# and not sol.
#
# Once again, this is a relatively cheap and maybe dirty version to gain access to lua_static from the
# internals of lua_sol

add_executable(demo_lua "source/demo_lua.cpp")
set_property(TARGET demo_lua PROPERTY CXX_STANDARD 20)
target_include_directories(demo_lua PRIVATE
    "third_party/lua_sol_cmake/lua_cmake/lua-5.4.7/src"
)
target_link_libraries(demo_lua PRIVATE lua_static)

install(
    TARGETS
        demo_chaiscript
        demo_pocketpy
        demo_lua_sol
        loading_lua_file
        demo_lua
    DESTINATION
        ${CMAKE_INSTALL_PREFIX}
)

install(
    DIRECTORY
        "assets"
    DESTINATION
        ${CMAKE_INSTALL_PREFIX}
)
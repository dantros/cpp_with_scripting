# C++ and Scripting

If you want to intergrate a scripting language into your C++ program, this may be a good reference. Current examples:

- Chaiscript: [demo_chaiscript.cpp](source/demo_chaiscript.cpp)
- Lua: [demo_lua.cpp](source/demo_lua.cpp)
- Lua via Sol2: [demo_lua_sol.cpp](source/demo_lua_sol.cpp), [loading_lua_file.cpp](source/loading_lua_file.cpp)
- Pocketpy (Python-like): [demo_pocketpy.cpp](source/demo_pocketpy.cpp)

After making a local clone, you need to initialize and update the git submodules by executing at the root of the repository:
```
git submodule update --init --recursive
```
Once you are done, you can generate the build files with cmake presets.
```
cmake --presets ninja-release
```
And then, just go to `../build_cmake/ninja-release/` and execute `ninja` and you will get your binary file.
You can also get a Visual Studio solution file for your convenience, check [CMakePresets.json](CMakePresets.json) file.

You should have [cmake](https://cmake.org/), [ninja](https://ninja-build.org/) and a compiler such as [Visual Studio Community](https://visualstudio.microsoft.com/vs/community/) availables in your development environment.

EOF

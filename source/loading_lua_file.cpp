#include <string>
#include <fstream>
#include <sstream>
#include <argparse/argparse.hpp>
#include <sol/sol.hpp>
#include <cassert>
#include <iostream>

int main(int argc, char *argv[])
{

    argparse::ArgumentParser program("loading_lua_file");

    std::string inputFilename;

    program.add_argument("-i", "--input")
        .help("file name of the lua file to process")
        .required()
        .store_into(inputFilename);

    try {
        program.parse_args(argc, argv);
    }
    catch (const std::exception& err) {
        std::cerr << err.what() << std::endl;
        std::cerr << program;
        return 1;
    }

    std::ifstream inputStream(inputFilename);
    std::stringstream inputBuffer;
    inputBuffer << inputStream.rdbuf();
    const std::string script = inputBuffer.str();

    sol::state lua;
    lua.open_libraries(sol::lib::base);

    lua.script(script);
}
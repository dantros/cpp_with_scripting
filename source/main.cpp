
#include <iostream>
#include <argparse/argparse.hpp>
#include <whereami2cpp.h>
#include <spdlog/spdlog.h>
#include <nlohmann/json.hpp>
#include <chaiscript/chaiscript.hpp>

double function(int i, double j)
{
    return i * j;
}

int main(int argc, char *argv[])
{
    argparse::ArgumentParser program("cpp_console_app", "0.1");

    program.add_argument("square")
        .help("display the square of a given integer")
        .scan<'i', int>();

    try {
        program.parse_args(argc, argv);
    }
    catch (const std::exception& err) {
        std::cerr << err.what() << std::endl;
        std::cerr << program;
        return 1;
    }

    auto input = program.get<int>("square");
    std::cout << (input * input) << std::endl;

    std::string executablePath = whereami::get_executable_path();
    std::cout << "whereami? -> " << executablePath << std::endl;

    spdlog::info("spdlog is working!");

    nlohmann::json jsonTest = nlohmann::json::parse(R"({"happy": true, "pi": 3.141})");
    std::cout << "jsonTest -> " << jsonTest.dump() << std::endl;

    chaiscript::ChaiScript chai;
    chai.add(chaiscript::fun(&function), "function");

    double d = chai.eval<double>("function(3, 4.75);");

    spdlog::info("chaiscript is working? -> function(3, 4.75) = {}", d);

    return 0;
}
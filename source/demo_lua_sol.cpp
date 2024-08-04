#include <sol/sol.hpp>
#include <cassert>
#include <iostream>

int main() {
    // Hello world test
    sol::state lua;
    int x = 0;
    lua.set_function("beep", [&x]{ ++x; });
    lua.script("beep()");
    assert(x == 1);

    // Something slightly more interesting
    lua.open_libraries(sol::lib::base);

	const auto& my_script = R"(
        local a,b,c = ...
        print(a,b,c)
    )";

    sol::load_result fx = lua.load(my_script);
	if (!fx.valid()) {
		sol::error err = fx;
		std::cerr << "failed to load string-based script into the program" << err.what() << std::endl;
	}
	
	// prints "your arguments here"
	fx("your", "arguments", "here");
}
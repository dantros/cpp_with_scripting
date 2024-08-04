
#include <iostream>
#include <string>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

int main()
{
    std::string cmd = "a = 5500 + 12 + (0.1 * math.sin(5512))";

	lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    int r = luaL_dostring(L, cmd.c_str());

    if (r == LUA_OK)
    {
        lua_getglobal(L, "a");
        if (lua_isnumber(L, -1))
        {
            float a = (float)lua_tonumber(L, -1);
            std::cout << "Value in C++ after calling Lua -> " << a << std::endl;
        }
    }
    else
    {
        std::string errormsg = lua_tostring(L, -1);
        std::cout << errormsg << std::endl;
    }

    lua_close(L);
	
	return 0;
}



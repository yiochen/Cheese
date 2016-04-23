#include <fstream>
#include <streambuf>
#include <string>
#include <iostream>
#include <sstream>
#include "lua.hpp"
using namespace std;
int main()
{
	/*
  std::ifstream file("config.lua");
  std::string script((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
  Lua lua;
  lua.RunScript(script);
  int width = lua.GetGlobalEnvironment().Get<int>("width");    // get the width
  int height = lua.GetGlobalEnvironment().Get<int>("height");  // get the height
  string windowTitle = lua.GetGlobalEnvironment().Get<string>("windowTitle");
  cout << "for winTittle" << endl;
  if (windowTitle.c_str() == NULL) {
	  cout << "string is null" << endl;
  }
  else {
	  cout << "the string is " << windowTitle << endl;
  }
 
  return width != 640 || height != 480;
  */

	lua_State *lua_state;
	lua_state = luaL_newstate();
	static const luaL_Reg lualibs[] =
	{
		{ "base", luaopen_base },
		{ NULL, NULL }
	};

	const luaL_Reg *lib = lualibs;
	for (; lib->func != NULL; lib++)
	{
		lib->func(lua_state);
		lua_settop(lua_state, 0);
	}

	// run the Lua script
	luaL_dofile(lua_state, "config.lua");
	cout << "printing returned value from the script" << endl;
	/*while (lua_gettop(lua_state)) {
		stringstream str_buf;
		str_buf.str(std::string());
		switch (lua_type(lua_state, lua_gettop(lua_state))){
		case LUA_TNUMBER:
			str_buf << "script returned the number:" << lua_tonumber(lua_state, lua_gettop(lua_state));
			break;
		case LUA_TSTRING:
			str_buf << "script returned the string: " << lua_tostring(lua_state, lua_gettop(lua_state));
			break;
		}
		lua_pop(lua_state, 1);
		cout << str_buf.str() << std::endl;
	}*/
	
	lua_getglobal(lua_state, "windowTitle");
	if (!lua_isstring(lua_state, -1)) {
		return -1;
	}
	else {
		printf("`var1' should be a number%s\n", lua_tostring(lua_state, -1));
	}
	
	cout << "finished parsing" << endl;
	// close the Lua state
	lua_close(lua_state);
	getchar();
}

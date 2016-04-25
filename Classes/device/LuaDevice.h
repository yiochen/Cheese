#pragma once
#include "luacppinterface/LuaCppInterface/luacppinterface.h"
#include <string>
#include <sstream>
/*this class is in charge of reading lua file and all the interaction between lua and c++*/

class LuaDevice {

private:
	bool initialized;
	static LuaDevice* s_instance;
	Lua* lua;//the only lua object that could exist at a time
	LuaDevice();
public:
	static LuaDevice *instance() {
		if (!s_instance) {
			s_instance = new LuaDevice();
		}
		return s_instance;
	}
	void init();
	Lua* getLua() { return lua; }
	bool load(std::string path);
	/*Load all the lua files */
	void loadAll();
	std::string getString(const std::string st) {
		std::stringstream ss;
		ss << st;
		return ss.str();
	}
	LuaTable global() {
		return lua->GetGlobalEnvironment();
	}
};


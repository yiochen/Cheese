#include "LuaDevice.h"
#include "device/TextReader.h"
#include "cocos2d.h"
USING_NS_CC;

LuaDevice *LuaDevice::s_instance = NULL;

LuaDevice::LuaDevice() {
	this->initialized = false;
	this->lua = NULL;
}

void LuaDevice::init() {
	if (!initialized) {
		lua = new Lua();
		lua->LoadStandardLibraries();
		this->initialized = true;
	}
}
bool LuaDevice::load(std::string path) {
	string script;
	bool success;
	script = device::read(path, success);
	CCLOG("back to the load function");
	//run the script
	if (success) {
		CCLOG("successfully load %s", path.c_str());
		string result=this->lua->RunScript(script);
		CCLOG("finshed running script");
		if (result.compare("No errors") == 0) {
			
			return true;
		}
		else {
			CCLOG("error running %s: %s", path.c_str(), result.c_str());
			return false;
		}
	}
	CCLOG("failed loading %s", path.c_str());
	return false;
}

void LuaDevice::loadAll() {
	//load all the lua file below
	load("lua/config.lua");
	load("lua/sprite_config.lua");
	load("lua/zombie_config.lua");
}
#include "Config.h"
#include "device/LuaDevice.h"
#include "cocos2d.h"
USING_NS_CC;
Config* Config::s_instance = nullptr;
Config::Config() {
	this->initialized = false;
}

void Config::init() {
	//use lua to initialize data
	if (!this->initialized) {
		auto luaConf = LuaDevice::instance()->global().Get<LuaTable>("config");
		this->debug_mode = luaConf.Get<bool>("debug_mode");
		this->fullscreen = luaConf.Get<bool>("fullscreen");
		this->screen_height = luaConf.Get<int>("screen_height");
		this->screen_width = luaConf.Get<int>("screen_width");
		
		this->WORLD_HEIGHT = luaConf.Get<int>("WORLD_HEIGHT");
		this->WORLD_WIDTH = luaConf.Get<int>("WORLD_WIDTH");
		
		if (debug_mode) CCLOG("debug mode");
		this->initialized = true;
	}
	
}
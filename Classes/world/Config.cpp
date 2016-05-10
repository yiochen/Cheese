#include "Config.h"
#include "device/LuaDevice.h"
#include "cocos2d.h"
USING_NS_CC;
Config* Config::s_instance = nullptr;
Config::Config() {
    
}

void Config::init() {
	//use lua to initialize data
	this->debug_mode = LuaDevice::instance()->global().Get<LuaTable>("config").Get<bool>("debug_mode");
	if (debug_mode) CCLOG("debug mode");
}
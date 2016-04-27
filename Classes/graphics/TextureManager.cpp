#include "graphics/TextureManager.h"
#include "device/LuaDevice.h"

TextureManager::TextureManager() {
    
}

void TextureManager::init() {
	//get the instance of the sprite cache;
	this->spriteCache = SpriteFrameCache::getInstance();
}

//load all the texture data needed for current level
//The prototype will change to take a parameter specifying the level file.
void TextureManager::load() {
	CCLOG("loading sprite cache");
	//load all the spritesheets
	//loading from lua file
	auto lua_sprite_config = LuaDevice::instance()->global().Get<LuaTable>("sprite_config");
	auto next_file_func = lua_sprite_config.Get<LuaFunction<LuaTable(int)>>("next_file");
	for (int i = 0; i < lua_sprite_config.Get<int>("total"); i++) {
		auto file_pair = next_file_func.Invoke(i);
		this->spriteCache->addSpriteFramesWithFile(file_pair.Get<std::string>(1), file_pair.Get<std::string>(2));
	}
}



//this is an expensive function, try retain the result as mush as possible
cocos2d::Vector<SpriteFrame*> TextureManager::getAnimation(const string name,const string action) {
	cocos2d::Vector<SpriteFrame*> animFrames;
	char st[100];
	int i = 1;
	sprintf(st, "%s_%s/%04d.png", name.c_str(), action.c_str(), i);
	CCLOG("the anim name is %s", st);
	SpriteFrame *frame;
	while ((frame=this->spriteCache->getSpriteFrameByName(st)) != NULL) {
		animFrames.pushBack(frame);
		i++;
		sprintf(st, "%s_%s/%04d.png", name.c_str(), action.c_str(), i);
	}
	return animFrames;

}

//unload the sprite cache
//used in transition of game level
void TextureManager:: unload() {
	CCLOG("uloading sprite cache");
}
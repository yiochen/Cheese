#pragma once
#include "cocos2d.h"
#include <unordered_map>
#include <string>

USING_NS_CC;
using namespace std;
//this class manages texture assets for this game
class TextureManager {
private:
	SpriteFrameCache* spriteCache;
public:
    TextureManager();
	void init();
	void load();
	void unload();
	~TextureManager() { unload(); }
	//int getFrameAmount(string name, string action);
	//set the sprite to 
	cocos2d::Vector<SpriteFrame*> getAnimation(const string name, const string action);
};

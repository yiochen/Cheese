#include "graphics/TextureManager.h"

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
	//TODO: this will use Lua later
	//load all the spritesheets
	this->spriteCache->addSpriteFramesWithFile("Assets/spritesheet/basic_zombie/BasicZombieSheet.plist", "Assets/spritesheet/basic_zombie/BasicZombieSheet.png");
	this->spriteCache->addSpriteFramesWithFile("Assets/spritesheet/swiss/SwissSheet.plist", "Assets/spritesheet/swiss/SwissSheet.png");
	
}



//this is an expensive function, try retain the result as mush as possible
cocos2d::Vector<SpriteFrame*> TextureManager::getAnimation(const string name,const string action) {

	CCLOG("name is %s and action is %s", name.c_str(), action.c_str());
	cocos2d::Vector<SpriteFrame*> animFrames;
	char st[100];
	int i = 1;
	sprintf(st, "%s/%s/%04d.png", name.c_str(), action.c_str(), i);
	SpriteFrame *frame;
	while ((frame=this->spriteCache->getSpriteFrameByName(st)) != NULL) {
		animFrames.pushBack(frame);
		i++;
		sprintf(st, "%s/%s/%04d.png", name.c_str(), action.c_str(), i);
	}
	return animFrames;

}

//unload the sprite cache
//used in transition of game level
void TextureManager:: unload() {
	CCLOG("uloading sprite cache");
}
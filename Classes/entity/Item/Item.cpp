#include "Item.h"
#include "world/World.h"
Item::Item() {
    
}

void Item::init() {
	Entity::init();
	this->sprite = Sprite::create();
	this->sprite->setUserData(this);
	this->sprite->setColor(Color3B::WHITE);
	this->sprite->setAnchorPoint(Vec2(0.5f, 0.5f));
	//add the empty sprite to game 
	World::instance()->getActionNode()->addChild(this->sprite);
	CCLOG("added item to world");
}
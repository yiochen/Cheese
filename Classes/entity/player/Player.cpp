#include "Player.h"
#include "Debug.h"
#include "cocos2d.h"
#include "world/World.h"
#include "graphics/TextureManager.h"
USING_NS_CC;

Player::Player() {
	//init sprite
	
}
void Player::init() {
	Entity::init();
	//TODO, for now, it will just create the sprite here, but later, move it to a component
	this->sprite = Sprite::create();
	this->sprite->setAnchorPoint(Vec2(0.5, 0));
	this->sprite->setUserData(this);
	this->sprite->setColor(Color3B::WHITE);
	//add the empty sprite to game 
	World::instance()->getActionNode()->addChild(this->sprite);
	CCLOG("added player to world");
	alliance = 0;
	
	
}


Player::~Player() {
	CCLOG("player is recycled");
	//World::instance()->playerList.remove(this);
}
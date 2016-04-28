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
	//add the empty sprite to game 
	World::instance()->getActionNode()->addChild(this->sprite);
	CCLOG("added player to world");
	alliance = 0;
	/*
	TextureManager* textureManager = World::instance()->getTextureManager();
	auto frames = textureManager->getAnimation("swiss", "WALK_FORTH");
	this->sprite = Sprite::createWithSpriteFrame(frames.front());
	World::instance()->getActionNode()->addChild(sprite);
	auto animation = Animation::createWithSpriteFrames(frames, 1.0f / 8);
	this->sprite->setPosition(Point(0, 0));
	this->sprite->runAction(RepeatForever::create(Animate::create(animation)));
	*/
	//add components
	
}


Player::~Player() {
	CCLOG("player is recycled");
	//World::instance()->playerList.remove(this);
}
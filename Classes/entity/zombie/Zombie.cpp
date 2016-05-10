#include "Zombie.h"
#include "world/World.h"
#include "graphics/TextureManager.h"

Zombie::Zombie() {
    
}

void Zombie::init() {
	//calling parent class init method
	Entity::init();
	player = NULL;
	this->sprite = Sprite::create();
	//this->sprite->setColor(Color3B::MAGENTA);
	this->sprite->setAnchorPoint(Vec2(0.5, 0));
	this->sprite->setUserData(this);
	this->sprite->setColor(Color3B::WHITE);
	//add the empty sprite to game 
	World::instance()->getActionNode()->addChild(this->sprite);

	/*
	TextureManager* textureManager = World::instance()->getTextureManager();
	auto frames = textureManager->getAnimation("basic_zombie", "WALK_FORTH");
	sprite = Sprite::createWithSpriteFrame(frames.front());
	World::instance()->getActionNode()->addChild(sprite);
	auto animation = Animation::createWithSpriteFrames(frames, 1.0f / 8);
	sprite->setPosition(Point(50, 0));
	sprite->runAction(RepeatForever::create(Animate::create(animation)));
	*/
}
Zombie::~Zombie() {
	CCLOG("zombie is recycled");
	//remove from the world
	//World::instance()->zombieList.remove(this);
}
#include "Player.h"
#include "Debug.h"
#include "cocos2d.h"
#include "world/World.h"
USING_NS_CC;

Player::Player() {
	//init sprite
	
}
void Player::init() {
	//TODO, for now, it will just create the sprite here, but later, move it to a component
	this->sprite = Sprite::createWithSpriteFrameName("WALK_LEFT/0001.png");
	//testSprite->initWithSpriteFrameName("Assets/spritesheet/swiss/WALK_BACK/0001.png");
	World::instance()->getActionNode()->addChild(sprite);
	this->sprite->setPosition(Point(0, 0));
}
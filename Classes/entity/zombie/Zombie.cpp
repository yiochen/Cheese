#include "Zombie.h"
#include "world/World.h"
#include "graphics/TextureManager.h"

Zombie::Zombie() {
    
}

void Zombie::init() {
	TextureManager* textureManager = World::instance()->getTextureManager();
	auto frames = textureManager->getAnimation("basic_zombie", "WALK_FORTH");
	sprite = Sprite::createWithSpriteFrame(frames.front());
	World::instance()->getActionNode()->addChild(sprite);
	auto animation = Animation::createWithSpriteFrames(frames, 1.0f / 8);
	sprite->setPosition(Point(50, 0));
	sprite->runAction(RepeatForever::create(Animate::create(animation)));
}

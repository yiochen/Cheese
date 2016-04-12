#include "AnimComp.h"
#include "world/World.h"
#include "KineticComp.h"
AnimComp::AnimComp() {
    
}


void AnimComp::init() {
	name = "";
	animState = "";
	newAnimState = "";
}


Animation* AnimComp::getAnimation(Entity* entity) {
	//get texture manager
	TextureManager* textureManager = World::instance()->getTextureManager();

	//get animation frames from the texture Manager
	if (name.length() > 0 && newAnimState.length() > 0) {
		auto frames = textureManager->getAnimation(name, newAnimState);
		//makesure the sprite is added to the display list 
		if (frames.size() >0) {
			//entity->sprite = Sprite::createWithSpriteFrame(frames.front());
			//World::instance()->getActionNode()->addChild(entity->sprite);

			auto animation = Animation::createWithSpriteFrames(frames, 1.0f / 8);
			//this->sprite->setPosition(Point(0, 0));
			//this->sprite->runAction(RepeatForever::create(Animate::create(animation)));

			//successfully created the animation
			return animation;
		}
	}
	
	return NULL;
}

void AnimComp::updateAnim(Entity* entity) {
	//get kinetic component of the entity, if the entity doesn't event have a position, don't bother playing it's animtion

	KineticComp* kin = static_cast<KineticComp*>(entity->components[COMP_CA::KINETIC_COMP]);
	if (kin) {
		//update the position of the sprite 
		entity->sprite->setPosition(Vec2(kin->pos));
	}
	if (kin && newAnimState != animState && newAnimState.length()>0) {
		Animation* ani = getAnimation(entity);
		if (ani) {
			//set 15 as the animation action tag
			entity->sprite->stopActionByTag(15);
			Action* aniAction=entity->sprite->runAction(RepeatForever::create(Animate::create(ani)));
			aniAction->setTag(15);
		}
	}
}

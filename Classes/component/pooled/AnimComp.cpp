#include "AnimComp.h"
#include "common_include.h"
#include "world/World.h"
#include "KineticComp.h"
#include "cocos2d.h"
#include "util/AnimNameHelper.h"
USING_NS_CC;
AnimComp::AnimComp() {
    
}


void AnimComp::init() {
	name = "";
	animState = "";
	newAnimState = "";
	isForced = false;
}

Animation* AnimComp::getAnimation(Entity* entity, std::string animState) {
	//get texture manager
	TextureManager* textureManager = World::instance()->getTextureManager();

	//get animation frames from the texture Manager
	if (name.length() > 0 && animState.length() > 0) {
		auto frames = textureManager->getAnimation(name, animState);
		//makesure the sprite is added to the display list 
		if (frames.size() >0) {
			auto animation = Animation::createWithSpriteFrames(frames, 1.0f / 8);
			//successfully created the animation
			return animation;
		}
	}

	return NULL;
}

Animation* AnimComp::getAnimation(Entity* entity) {
	return getAnimation(entity, newAnimState);
}

void AnimComp::updateAnim(Entity* entity) {
	//get kinetic component of the entity, if the entity doesn't event have a position, don't bother playing it's animtion

	KineticComp* kin = static_cast<KineticComp*>(entity->components[COMP_CA::KINETIC_COMP]);
	if (kin) {
		//update the position of the sprite 
		//TODO: convert world location to screen location 
		entity->sprite->setPosition(Vec2(kin->pos));
		entity->sprite->setLocalZOrder(-entity->sprite->getPosition().y);
		//check the velocity angle, change the animation state
		float speed = kin->vel.getLength();
		if (speed <= EPSILON) {
			//if the player is not moving, dont change the animation
		}
		else {
			float angle = kin->vel.getAngle();
			this->newAnimState = anim_name::directionalString(A_WALK, kin->vel);
			//if (angle < PI / 4 && angle > -PI / 4) {
			//	//moving right 
			//	this->newAnimState = A_WALK_RIGHT;
			//}
			//else if (angle >= PI / 4 && angle < 3 * PI / 4) {
			//	this->newAnimState = A_WALK_BACK;
			//	//moving up
			//}
			//else if (angle >= 3 * PI / 4 || angle < -3 * PI / 4) {
			//	this->newAnimState = A_WALK_LEFT;
			//	//moving left
			//}
			//else {
			//	this->newAnimState = A_WALK_FORTH;
			//	//moving forward
			//}

		}
		
	}
	auto forcePlaying = entity->sprite->getActionByTag(16);
	if (forcePlaying && forcePlaying->isDone()) {
		forcePlaying->release();
		isForced = false;
		forcePlaying = NULL;
	}
	if (forcePlaying==NULL && kin && newAnimState != animState && newAnimState.length()>0) {
		Animation* ani = getAnimation(entity);
		if (ani) {
			//set 15 as the animation action tag
			entity->sprite->stopActionByTag(15);
			Action* aniAction=entity->sprite->runAction(RepeatForever::create(Animate::create(ani)));
			this->animState = newAnimState;
			aniAction->setTag(15);
		}
	}
}
void AnimComp::forcePlay(Entity* entity, std::string animation, int loop) {
	isForced = true;
	Animation* ani = getAnimation(entity, animation);
	if (ani) {
		CCLOG("force playing");
		entity->sprite->stopActionByTag(15);
		entity->sprite->stopActionByTag(16);
		Action* aniAction = entity->sprite->runAction(Repeat::create(Animate::create(ani),loop));
		aniAction->setTag(16);
		isForced=true;
		animState = "";
	}
}

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
	pendingRemoval = 0;
	//Default action is walk, and it has 4 animation 
	defaultAction = A_WALK;
	int directional = 4;
}

Animation* AnimComp::getAnimation(Entity* entity, std::string animState) {
	//get texture manager
	TextureManager* textureManager = World::instance()->getTextureManager();
//	CCLOG("%s getting %s", this->name.c_str(),animState.c_str());
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
	if (entity->sprite == NULL) return;
	//get kinetic component of the entity, if the entity doesn't event have a position, don't bother playing it's animtion
	auto pendingRemovalAction = entity->sprite->getActionByTag(pendingRemoval);
	if (pendingRemoval > 0 && (!pendingRemovalAction || pendingRemovalAction->isDone())) {
		//remove the sprite
		if (entity->sprite) {
			entity->sprite->removeFromParentAndCleanup(true);
		}
		entity->sprite = NULL;
		entity->marked = true;
		return;
	}
	KineticComp* kin = (KineticComp*)(entity->components[COMP_CA::KINETIC_COMP]);
	if (kin) {
		//update the position of the sprite 
		//TODO: convert world location to screen location 
		entity->sprite->setPosition(Vec2(kin->pos));
		entity->sprite->setLocalZOrder(-entity->sprite->getPosition().y);
		//CCLOG("the pos is at %f,%f", entity->sprite->getPositionX(), entity->sprite->getPositionY());
		//check the velocity angle, change the animation state
		float speed = kin->vel.getLength();
		if (speed <= EPSILON) {
			//if the player is not moving, dont change the animation
		}
		else {
			float angle = kin->vel.getAngle();
			switch (this->directional) {
				case 4: 
					this->newAnimState = anim_name::directionalString(this->defaultAction, kin->vel);
					break;
				case 0:
					this->newAnimState = this->defaultAction;
					CCLOG("the new animState is %s, the default action is %s, the name is %s", this->newAnimState.c_str(), this->defaultAction.c_str(), this->name.c_str());
					break;
			}
			
		}
		
	}
	auto forcePlaying = entity->sprite->getActionByTag(16);
	//if (forcePlaying) CCLOG("it has forceplaying, so strange");
	if (forcePlaying && forcePlaying->isDone()) {
		forcePlaying->release();
		isForced = false;
		forcePlaying = NULL;
	}
	if (forcePlaying==NULL && kin && newAnimState != animState && newAnimState.length()>0) {
		//CCLOG("changing anim state, the animState is %s and the newAnimState is %s",animState.c_str(),newAnimState.c_str());
		Animation* ani = getAnimation(entity);
		if (ani) {
			//CCLOG("found animstate");
			//set 15 as the animation action tag
			entity->sprite->stopActionByTag(15);
			Action* aniAction=entity->sprite->runAction(RepeatForever::create(Animate::create(ani)));
			this->animState = newAnimState;
			aniAction->setTag(15);
		}
	}
}
void AnimComp::forcePlay(Entity* entity, std::string animation, int loop, bool removeAfterPlay) {
	if (!entity->sprite || this->pendingRemoval) return;//if already pending removal, don't change the animation 
	CCLOG("forcePlaying %s animation", animation.c_str());
	isForced = true;
	Animation* ani = getAnimation(entity, animation);
	if (ani) {
		CCLOG("force playing");
		entity->sprite->stopActionByTag(15);
		entity->sprite->stopActionByTag(16);
		Action* aniAction = entity->sprite->runAction(Repeat::create(Animate::create(ani), loop));
		
		if (removeAfterPlay) {
			pendingRemoval = 16;
		}
		aniAction->setTag(16);
		isForced=true;
		animState = "";
	}
}
void AnimComp::forcePlay(Entity* entity, std::string animation, int loop) {
	this->forcePlay(entity, animation, loop, false);
}

#include "AnimComp.h"
#include "common_include.h"
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
			auto animation = Animation::createWithSpriteFrames(frames, 1.0f / 8);
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
			if (angle < PI / 4 && angle > -PI / 4) {
				//moving right 
				this->newAnimState = A_WALK_RIGHT;
			}
			else if (angle >= PI / 4 && angle < 3 * PI / 4) {
				this->newAnimState = A_WALK_BACK;
				//moving up
			}
			else if (angle >= 3 * PI / 4 || angle < -3 * PI / 4) {
				this->newAnimState = A_WALK_LEFT;
				//moving left
			}
			else {
				this->newAnimState = A_WALK_FORTH;
				//moving forward
			}

		}
		
	}
	if (kin && newAnimState != animState && newAnimState.length()>0) {
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

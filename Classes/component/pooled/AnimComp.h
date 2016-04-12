#pragma once
#include <string>
#include "cocos2d.h"
#include "component/PooledComponent.h"
#include "entity/Entity.h"

USING_NS_CC;

//This component store the display information
//including sprite, animation state
//it provides helper function to change the animation and also update the sprites location on the screen
class AnimComp :public PooledComp{
public:
	std::string name;
	std::string animState;

	//if you want to change the animation currently playing, change the newAnimState.
	std::string newAnimState;
    AnimComp();

	//helper function to get the Animation
	Animation* getAnimation(Entity* entity);

	//Update the animation currently playing if not correct, move the sprite to the designated place
	//precondition: the sprite should have been added already
	void updateAnim(Entity* entity);
	void init() override;
};


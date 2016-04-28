#pragma once
#include <string>
#include "component/CompHeader.h"

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
	//forcely change the playing animation without changing the animState.
	//This is use to play some short-term animation such as attacking or healing. 
	//After this is run, the animation will be set back to animState
	bool isForced;
	//the action tag to wait for, when the action is done, remove the entity
	int pendingRemoval;
    AnimComp();

	//helper function to get the Animation
	Animation* getAnimation(Entity* entity);
	Animation* getAnimation(Entity* entity, std::string animState);

	//Update the animation currently playing if not correct, move the sprite to the designated place
	//precondition: the sprite should have been added already
	void updateAnim(Entity* entity);
	void forcePlay(Entity* entity, std::string animation, int loop);
	void forcePlay(Entity* entity, std::string animation, int loop, bool removeAfterPlay);
	void init() override;
};


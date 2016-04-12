#pragma once
#include "EntityRunner.h"

//The purpose of the keyboard runner is to update entity's velocity for entities that have keyboardComponent (user controled entity)
//For other entities that are not directly controlled by user input, use other runners to update their veloity
class KeyboardRunner:public EntityRunner {
public:
    KeyboardRunner();
	void update(float delta) override;
};

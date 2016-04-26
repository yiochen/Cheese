#include "ActionFlagComp.h"
#include "world/World.h"
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocostudio::timeline;
ActionFlagComp::ActionFlagComp() {
    
}

void ActionFlagComp::init() {
	isReady = false;
	isWaiting = false;
	interval = 0;
	time = 0;
}
void ActionFlagComp::schedule() {
	this->isWaiting = true;
	this->time = interval;
}
void ActionFlagComp::update(float delta) {
	if (this->isWaiting) {
		this->time -= delta;
		if (this->time < 0) {
			this->acting();
		}
	}
}
void ActionFlagComp::acting() {
	this->isWaiting = false;
	this->isReady = true;
	this->time = 0;
	
}
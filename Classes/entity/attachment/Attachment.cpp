#include "Attachment.h"
#include "common_include.h"
#include "util/AnimNameHelper.h"
#include "graphics/TextureManager.h"
#include "world/World.h"

Attachment::Attachment() {
    
}

Attachment::~Attachment() {

}

void Attachment::initAttachment() {
	loop = 1;//by default, play the animation once
	interruptable = false;
	queueable = true;
	autoremove = true;
	finished = false;
	isStarted = false;
	this->setPosition(Vec2(0, 0));
	this->name = "";//set empty string as the initial string.
}

/* return true if successfully set the animName*/
bool Attachment::setAnim(std::string name) {
	/*If the attachment is already started, it cannot be replayed*/
	if (isStarted) {
		CCLOG("Attachment animation is already started with %s, cannot play %s", this->name, name);
		return false;
	}
	/*If the animation has not started (it might be in the queue)*/
	if (name.length() > 0) {
		this->name = name;
	}
	else {
		CCLOG("cannot set a anim name to empty string");
		return false;
	}
	
	return true;
}

/* return true is successfully playing*/
bool Attachment::play() {
	if (this->name.length()==0) {
		CCLOG("Attachment's name is empty");
		return false;
	}
	if (this->loop <= 0) {
		CCLOG("loop smaller than 1");
		return false;
	}
	//find the animation from the TextureManager
	TextureManager* textureManager = GET_WORLD->getTextureManager();
	auto frames = textureManager->getAnimation(EFFECT_STR, name);
	if (frames.size() > 0) {
		auto animation = Animation::createWithSpriteFrames(frames, ANIM_RATE);
		this->runAction(Repeat::create(Animate::create(animation), this->loop));
		this->isStarted = true;
	}
	
	
	return this->isStarted;
}

void Attachment::finish() {
	this->isStarted = true;
	this->finished = true;
	this->removeAllChildrenWithCleanup(true);
	this->cleanup();
}
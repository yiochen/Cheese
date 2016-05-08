#pragma once
#include "cocos2d.h"

USING_NS_CC;
/*attachment are some visual effect that can be attach to another sprite*/
/*Usage:
	get an Attachment from the objectpool,
	call initAttachment to initialize it,
	tune the field value if needed, 
	add to list of the entity,
	call play function of the attachment*/
class Attachment: public Sprite{
public:
	//attributes
	/*If the animation could be interrupted*/
	bool interruptable;
	/*If it can be queued. If true, it will be added to queue if the animation queue has something already*/
	bool queueable;
	/*if the attachment can be concurrently played with other attachments. if true, it cannot be queueable*/
	bool concurrent;
    Attachment();
	
	std::string name;
	int loop;
	bool finished;
	bool isStarted;
	
	virtual ~Attachment();

	/*since init is defined in Sprite, we call it initAttachment instead*/
	void initAttachment();
	/*start playing the animation, note that if this animation is queueable and is not the first of the animation, it will be queue*/
	bool setAnim(std::string name);
	/*This is called by a runner to actually start playing the animation, The runner needs to make sure that this is at the head of the list*/
	bool play();
	/*stop the animation immediately. */
	void finish();
};

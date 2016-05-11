#pragma once
#include <unordered_map>
#include "component/ComponentCatalog.h"
#include "component/Component.h"
#include "component/PooledComponent.h"
#include "entity/attachment/Attachment.h"
#include "cocos2d.h"
#include "attachment/Attachment.h"
USING_NS_CC;
/*
*	Entity is an abstract class
*/
class Entity {
public:
	/*If an entity is marked, that means it is ready to be deleted. It will be deleted in the last runner. */
	bool marked;
	int alliance;
	Color3B color;
	std::unordered_map<COMP_CA, Comp*> components;
	std::list<Attachment*> attachments;
	void addAttachment(Attachment* attachment);
	//remove all the attachment of this name
	void removeAttachment(std::string name);
	void removeAllAttachment();
	//std::unordered_map<COMP_CA, PooledComp*> pooledComponents;
	virtual void init();//the default entity init function doesn't do anything
    Entity();
	virtual ~Entity();
	virtual void cleanup();
	Sprite* sprite;
	//tint the sprite's color
	void tint(Color3B color);
	//if set the sprite's color to this->color
	void tint();
	//remove tint (tint to white)
	void untint();
	Color3B getColor();
};

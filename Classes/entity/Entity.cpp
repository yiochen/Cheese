#include "Entity.h"
#include "world/World.h"
#include "cocos2d.h"
#include "world/world_include.h"
USING_NS_CC;
#define DELETE_COMP(T, e) do{World::instance()->getCompPool<T>(e)->Delete((T*)this->components[e]); this->components[e]=NULL;}while(0)
Entity::Entity() {
    
}

Entity::~Entity() {
	//TODO
	//free all resource
	cleanup();
	//set all pointers to NULL
	//remove all the components from the component list
	sprite = NULL;
}

void Entity::cleanup() {
	CCLOG("recycling entity");
	//remove all component
	World* world = World::instance();
	//only need to clean up the pooled comp
	//ActionFlagComp
	//world->getCompPool<ActionFlagComp>(COMP_CA::ACTION_FLAG_COMP)->Delete((ActionFlagComp*)this->components[COMP_CA::ACTION_FLAG_COMP]);
	DELETE_COMP(ActionFlagComp, COMP_CA::ACTION_FLAG_COMP);
	DELETE_COMP(AnimComp, COMP_CA::ANIM_COMP);
	DELETE_COMP(CombatComp, COMP_CA::COMBAT_COMP);
	DELETE_COMP(DomainComp, COMP_CA::DOMAIN_COMP);
	DELETE_COMP(HealComp, COMP_CA::HEAL_COMP);
	DELETE_COMP(HordeStatusComp, COMP_CA::HORDE_STATUS_COMP);
	DELETE_COMP(KineticComp, COMP_CA::KINETIC_COMP);
	DELETE_COMP(ZombieSensorComp, COMP_CA::ZOMBIE_SENSOR_COMP);
	//clean up the component array
	this->components.clear();
}
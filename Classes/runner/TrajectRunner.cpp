#include "TrajectRunner.h"
#include "entity/Item/Item.h"
#include "world/World.h"
#include "component/pooled/TrajectComp.h"
#include "component/pooled/KineticComp.h"
TrajectRunner::TrajectRunner() {
    
}
void TrajectRunner::update(float delta) {

	//we know that only item(bullet) has TrajectComp, so we only iterate throug itemList
	//unless some flying zombies?
	World * world = World::instance();
	auto itemIt = world->itemList.begin();
	while (itemIt != world->itemList.end()) {
		updateEntity(*itemIt, delta);
		itemIt++;
	}
}

void TrajectRunner::updateEntity(Entity* entity, float delta) {
	if (!entity) return;
	//get all the required components
	TrajectComp* traject = (TrajectComp*)entity->components[COMP_CA::TRAJECT_COMP];
	KineticComp* kinetic = (KineticComp*)entity->components[COMP_CA::KINETIC_COMP];
	if (traject && kinetic) {
		//for now, just move the entity in straight line. 
		traject->update(entity, delta);
	}
}
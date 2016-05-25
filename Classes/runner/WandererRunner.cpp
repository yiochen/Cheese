#include "WandererRunner.h"
#include "entity/zombie/Zombie.h"
#include "world/World.h"
#include "component/pooled/KineticComp.h"
#include "component/pooled/WanderingComp.h"


USING_NS_CC;
WandererRunner::WandererRunner() {

}

void WandererRunner::update(float delta) {
	//iterate over zombie
	World* world = World::instance();
	auto zombieIt = world->zombieList.begin();
	auto playerIt = world->playerList.begin();
	while (playerIt != world->playerList.end()) {
		updateEntity((Player*)*playerIt, delta);
		playerIt++;
	}
	while (zombieIt != world->zombieList.end()) {
		updateEntity(*zombieIt, delta);
		zombieIt++;
	}
}

void WandererRunner::updateEntity(Entity* entity, float delta) {
	KineticComp* kineticComp = (KineticComp*)entity->components[COMP_CA::KINETIC_COMP];
	WanderingComp* wanderingComp = (WanderingComp*)entity->components[COMP_CA::WANDERING_COMP];
//	CCLOG("i am this far away %f", wanderingComp->target.distance(kineticComp->pos));
	if (kineticComp && wanderingComp) {
		
		if (wanderingComp->arrived(entity)) {
			
			wanderingComp->newTarget();
			kineticComp->vel.setZero();
		}
		else {

			Vec2 change(wanderingComp->target - kineticComp->pos);
			change.scale(delta);
			kineticComp->vel.add(change);
			if (kineticComp->vel.getLength() > kineticComp->maxSpeed) {
				kineticComp->vel.normalize();
				kineticComp->vel.scale(kineticComp->maxSpeed);
			}
			
		}
	}
	
}
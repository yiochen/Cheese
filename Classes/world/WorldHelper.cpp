#include "WorldHelper.h"
#include "world_include.h"

//destroy all the component Object Pools. 
//yeah, I know, this is painful..But I couldn't find other way to do this
void world_helper::destroyCompPools(World* world) {
	//it's ok to delete NULL
	delete world->getCompPool<KineticComp>(COMP_CA::KINETIC_COMP);
	delete world->getCompPool<AnimComp>(COMP_CA::ANIM_COMP);
	delete world->getCompPool<DomainComp>(COMP_CA::DOMAIN_COMP);
	delete world->getCompPool<HordeStatusComp>(COMP_CA::HORDE_STATUS_COMP);
	delete world->getCompPool<CombatComp>(COMP_CA::COMBAT_COMP);
	delete world->getCompPool<ActionFlagComp>(COMP_CA::ACTION_FLAG_COMP);
	delete world->getCompPool<WanderingComp>(COMP_CA::WANDERING_COMP);
	delete world->getCompPool<TrajectComp>(COMP_CA::TRAJECT_COMP);
	delete world->getCompPool<PointComp>(COMP_CA::POINT_COMP);
	delete world->getCompPool<PowerUpComp>(COMP_CA::POWER_UP_COMP);
	
	world->compPools.clear();
}
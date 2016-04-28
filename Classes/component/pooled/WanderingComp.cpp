#include "world/Config.h"
#include "component/pooled/WanderingComp.h"

WanderingComp::WanderingComp() {
	
}

WanderingComp::~WanderingComp() {

}
void WanderingComp::init() {
	isChasing = true; 
	Config* config = Config::instance();
	target.set(RandomHelper::random_real<float>(0, config->WORLD_WIDTH), RandomHelper::random_real<float>(0, config->WORLD_HEIGHT));

}
void WanderingComp::newTarget(Entity* entity) {
	Config* config = Config::instance();
	WanderingComp* wand = static_cast<WanderingComp*>(entity->components[COMP_CA::WANDERING_COMP]);
	wand->target.set(RandomHelper::random_real<float>(0, config->WORLD_WIDTH), RandomHelper::random_real<float>(0, config->WORLD_HEIGHT));
	CCLOG("New location is %f %f", target.x, target.y);

}
#include "world/Config.h"
#include "component/pooled/WanderingComp.h"
#include "component/pooled/KineticComp.h"
WanderingComp::WanderingComp() {
	
}

WanderingComp::~WanderingComp() {

}
void WanderingComp::init() {
	isChasing = true; 
	Config* config = Config::instance();
	target.set(RandomHelper::random_real<float>(0, config->WORLD_WIDTH), RandomHelper::random_real<float>(0, config->WORLD_HEIGHT));

}
void WanderingComp::newTarget() {
	Config* config = Config::instance();
	
	this->target.set(RandomHelper::random_real<float>(0, config->WORLD_WIDTH), RandomHelper::random_real<float>(0, config->WORLD_HEIGHT));
	
}
bool WanderingComp::arrived(Entity* entity) {
	KineticComp* kin = (KineticComp*)entity->components[COMP_CA::KINETIC_COMP];
	auto dir = this->target - kin->pos;
	
	if (dir.dot(kin->vel) < 0) {
		return true;
	}
	return false;
}
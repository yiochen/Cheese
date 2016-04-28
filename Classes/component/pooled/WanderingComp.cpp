#include "world/Config.h"
#include "component/pooled/WanderingComp.h"

WanderingComp::WanderingComp() {
	isChasing = true;
	newTarget();
}

WanderingComp::~WanderingComp() {

}
void WanderingComp::newTarget() {
	Config* config = Config::instance();
	target.set(RandomHelper::random_real<float>(0, config->WORLD_WIDTH), RandomHelper::random_real<float>(0, config->WORLD_HEIGHT));
}
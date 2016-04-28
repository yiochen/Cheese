#include "ZombieSpawningPool.h"
#include "EntityFactory.h"

USING_NS_CC;

ZombieSpawningPool::ZombieSpawningPool() {

}
ZombieSpawningPool::ZombieSpawningPool(float TIME) {
	interval = TIME;
}

void ZombieSpawningPool::init() {
	isReady = true;
	isWaiting = false;
	time = 0;
}

void ZombieSpawningPool::schedule() {
	this->isReady = false;
	this->isWaiting = true;
	this->time = interval;
}
void ZombieSpawningPool::update(float delta) {
	if (isReady) {
		spawnStrayZombie();
	}
	if (this->isWaiting) {
		this->time -= delta;
		if (this->time < 0) {
			this->acting();
		}
	}
}
void ZombieSpawningPool::acting() {
	this->isWaiting = false;
	this->isReady = true;
	this->time = 0;

}
void ZombieSpawningPool::spawnStrayZombie() {
	
	EntityFactory::createStrayZombie((ZOMBIE_CA)RandomHelper::random_int(0, 2));
	schedule();
}
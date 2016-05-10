#include "ZombieSpawningPool.h"
#include "EntityFactory.h"

USING_NS_CC;

ZombieSpawningPool::ZombieSpawningPool() {
	World* world = World::instance();
	auto lua = LuaDevice::instance();
	LuaTable global = lua->global();

	

	strayInterval = global.Get<int>("straySpawn");
	bossInterval = global.Get<int>("bossSpawn");
	isReadyStray = false;
	isWaitingStray = false;
	isReadyBoss = false;
	isWaitingBoss = false;
}

void ZombieSpawningPool::init() {
	isReadyStray = false;
	isWaitingStray = true;
	isReadyBoss = false;
	isWaitingBoss = true;
	strayTime = strayInterval;
	totalTime = 0;
	bossTime = bossInterval;
}

void ZombieSpawningPool::scheduleStray() {
	this->isReadyStray = false;
	this->isWaitingStray = true;
	this->strayTime = strayInterval;
}
void ZombieSpawningPool::scheduleBoss() {
	this->isReadyBoss = false;
	this->isWaitingBoss = true;
	this->bossTime = bossInterval;
}
void ZombieSpawningPool::update(float delta) {

	if (isReadyStray) {
		spawnStrayZombie();
	}
	if (isReadyBoss) {
		spawnMiniBossZombie();
	}
	if (this->isWaitingStray) {
		this->strayTime -= delta;
		if (this->strayTime < 0) {
			this->isWaitingStray = false;
			this->isReadyStray = true;
			this->strayTime = 0;
		}
	}
	if (this->isWaitingBoss) {
		this->bossTime -= delta;
		if (this->bossTime < 0) {
			this->isWaitingBoss = false;
			this->isReadyBoss = true;
			this->bossTime = 0;
		}
	}
	this->totalTime += delta;
	World* world = World::instance();
	world->infoPanel->updateTime();

}
void ZombieSpawningPool::spawnStrayZombie() {
	
	EntityFactory::createStrayZombie((ZOMBIE_CA)RandomHelper::random_int(0, 1));
	scheduleStray();
}
void ZombieSpawningPool::spawnMiniBossZombie() {

	EntityFactory::createPlayer(false,false, totalTime);
	scheduleBoss();
}
#pragma once
#include "cocos2d.h"


/*this component has a timer.
It will spawn a random zombie when the time runs out*/
class ZombieSpawningPool  {

public:
	bool isReady;
	bool isWaiting;
	float interval;

	float time;
	ZombieSpawningPool();
	ZombieSpawningPool(float);
	void init();
	void schedule();
	void update(float delta);
	void spawnStrayZombie();
private:
	void acting();
};

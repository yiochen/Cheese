#pragma once
#include "cocos2d.h"


/*this component has a timer.
It will spawn a random zombie when the time runs out*/
class ZombieSpawningPool  {

public:
	bool isReadyStray, isReadyBoss;
	bool isWaitingStray, isWaitingBoss;

	//stray zombie interval
	float strayInterval;
	float bossInterval;
	

	float strayTime, bossTime, totalTime;
	ZombieSpawningPool();
	void init();
	void scheduleStray();
	void scheduleBoss();
	void update(float delta);
	void spawnStrayZombie();
	void spawnMiniBossZombie();
	
private:
};

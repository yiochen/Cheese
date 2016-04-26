#pragma once
#include "component/CompHeader.h"
#include "entity/zombie/Zombie.h"
#include "cocos2d.h"
/*This component make up the disadvantage of the distributed model in which zombies only knows about itself. In this component, you can record information of the neighboring zombies*/
class ZombieSensorComp : public PooledComp{
public:
	Zombie* closestAlliance;
	Vec2 allianceDis;
	Zombie* closestEnemy;
	Vec2 enermyDis;
    ZombieSensorComp();
	void init() override;
	/*clean function will reset all the data.
	It sets all the pointers to NULL in order to prevent memory access violation*/
	void clean();
};

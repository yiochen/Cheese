#pragma once
#include "component/CompHeader.h"

/*This component keeps track of the ammount of each zombie types and their locational distribution in the horde*/
class HordeStatusComp:public PooledComp {
public:
	std::unordered_map<ZOMBIE_CA, int> zombieCounts;
	std::unordered_map<ZOMBIE_STAT_CA, float> zombieStat;
	int pointsRemaining;
	Vec2 sumPos;//The sum of all zombies position. This is used to calculate the average position of all zombies
	int total;
    HordeStatusComp();
	void zeroPos();
	void init() override;
	void updateHorde();
};

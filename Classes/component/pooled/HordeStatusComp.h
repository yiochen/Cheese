#pragma once
#include "component/CompHeader.h"

//TODO: use the following struct for zombieStat map
//use common word for differnt type of zombie, for example chucker's attack and holy's heal are the same field.
typedef struct _ZStat {
	int hp;
	int attack;
	int attackSpeed;
} ZStat;

/*This component keeps track of the ammount of each zombie types and their locational distribution in the horde*/
class HordeStatusComp:public PooledComp {
public:
	std::unordered_map<ZOMBIE_CA, int> zombieCounts;
	//TODO: it's better to have use a struct that contains same fields for all the zombies, then make a map of the structs.
	//because right now we have to check ZOMBIE type and then manually use if or switch to check field. If multiple places use zombieStat, then we have to change multiple place when something changes
	std::unordered_map<ZOMBIE_STAT_CA, float> zombieStat;
	std::unordered_map<ZOMBIE_CA, ZStat> zombieStats;
	//use something like this--- std::unordered_map<ZOMBIE_CA, Zstat> zombieStat;
	//and call like this--- zombieStat[ZOMBIE_CA::CHUCKER].hp=5;
	int pointsRemaining;
	Vec2 sumPos;//The sum of all zombies position. This is used to calculate the average position of all zombies
	int total;
    HordeStatusComp();
	void zeroPos();
	void init() override;
	void updateHorde();
	void updateStray(Entity* e);

	//temporary function for healer to use
	int getMaxHP(ZOMBIE_CA zombieType);
};


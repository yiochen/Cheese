#pragma once
#include "component/CompHeader.h"

/*Combat comp will include all the properties of this individual zombie
includes health, atkspeed and other properties that may not be used*/
class CombatComp :public PooledComp {
public:
	float attackSpeed;
	int hp;
	int damage;
	/*alliance is a number representing the side of zombie. If two zombie have the same alliance, they donnot fight. Otherwise they will fight.*/
	int alliance;
	/*The damage pending to be inflicted on the entity. This is used so that there could be multiple damage source and the invisiblity effect could ignore all the pending damages*/
	int pendingDmg;
	CombatComp();
	void init() override;
	void setHP(int);
	void setDamage(int);
	void setAttackSpeed(float);
};

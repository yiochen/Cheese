#pragma once
#include "component/CompHeader.h"

/*Combat comp will include all the properties of this individual zombie
includes health, atkspeed and other properties that may not be used*/
class CombatComp :public PooledComp {
public:
	float attackSpeed;
	int hp;
	int damage;
	CombatComp();
	void setHP(int);
	void setDamage(int);
	void setAttackSpeed(float);
};

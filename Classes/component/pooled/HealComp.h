#pragma once
#include "component/CompHeader.h"

/*Combat comp will include the healing properties of this zombie*/
class HealComp :public PooledComp {
public:
	int heal;
	float healSpeed;
	HealComp();
	void setHeal(int);
	void setHealSpeed(float);
};

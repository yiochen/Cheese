#pragma once
#include "component/CompHeader.h"
/*Entity with this comp will move in a trajectory toward a target. */
class TrajectComp:public PooledComp{
public:
    TrajectComp();
	void init() override;
	void update(Entity* entity);
};

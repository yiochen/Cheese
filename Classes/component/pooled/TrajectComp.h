#pragma once
#include "component/CompHeader.h"
/*Entity with this comp will move in a trajectory toward a target. */
/*Important: Since entity with trajectory will strictly follow the path, velocity of the entity itself will not be taken into calculation. instead, it has it's own speed field */
class TrajectComp:public PooledComp{
public:
    TrajectComp();
	void init() override;
	void launch(Vec2 origin, Vec2 target);
	void update(Entity* entity, float delta);
	float speed;// the speed that it will move in the shortest distance
	Vec2 curPos;//the current position of the entity if it follows the straight shotest path. 
	Vec2 origin;
	Vec2 target;
	bool arrived;
};

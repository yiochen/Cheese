#pragma once
#include "component/CompHeader.h"

/*Domain Component is used for an entity to mark a circle range of domain,
It could be used by player to mark the range that the following zombies should try to stay in. 
It could also be used by a bomb to represent the range that it can cause damage to*/
class DomainComp:public PooledComp {
public:
	float radius;
    DomainComp();
	bool contains(Vec2 center, Vec2 target);
};

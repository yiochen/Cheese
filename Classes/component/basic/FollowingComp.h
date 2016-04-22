#pragma once
#include "component/CompHeader.h"

/*Entity with this component will follow the other entity.
The follower's velocity will be affected by the leader's velocity
This is a marker class*/
class FollowingComp :public Comp{
public:
    FollowingComp();
	void follow(Entity* self, Entity* target, float delta);
};

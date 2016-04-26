#pragma once
#include "component/CompHeader.h"
#include "cocos2d.h"

/*this component has a timer. 
The action (combat or heal) will be executed when the timer runs out*/
class ActionFlagComp:public PooledComp {

public:
	bool isReady;
	bool isWaiting;
	float interval;
	
	float time;
    ActionFlagComp();
	void init() override;
	void schedule();
	void update(float delta);
private:
	void acting();
};

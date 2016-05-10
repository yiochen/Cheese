#pragma once
#include "component/CompHeader.h"

USING_NS_CC;

/*points that this character scored
*/
class PointComp :public PooledComp {
public:
	
	PointComp();
	int point;
	void init() override;
	void add(Entity*, int);
	~PointComp() {}
};

#pragma once
#include "component/Component.h"
class PooledComp:public Comp {
public:
    PooledComp();
	virtual void init() {};
};

#pragma once
#include "entity/Entity.h"
class Item:public Entity {
public:
	void init() override;
    Item();
};

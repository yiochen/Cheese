#pragma once
#include "EntityRunner.h"
class KeyboardRunner:public EntityRunner {
public:
    KeyboardRunner();
	void update(float delta) override;
};

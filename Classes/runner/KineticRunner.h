#pragma once
#include "EntityRunner.h"
class KineticRunner :public EntityRunner {
public:
	KineticRunner();
	void update(float delta) override;
};

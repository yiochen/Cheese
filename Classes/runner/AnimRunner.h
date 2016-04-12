#pragma once
#include "runner/EntityRunner.h"
#include "entity/Entity.h"
class AnimRunner:public EntityRunner {
private:
	void runAnimRunner(Entity* entity);
public:
    AnimRunner();
	void update(float delat) override;

};

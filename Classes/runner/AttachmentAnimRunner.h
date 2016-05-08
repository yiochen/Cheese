#pragma once
#include "entity/Entity.h"
#include "EntityRunner.h"
class AttachmentAnimRunner: public EntityRunner {
private:
	void updateEntity(Entity* entity, float delta);
public:
    AttachmentAnimRunner();
	void update(float delta) override;
};

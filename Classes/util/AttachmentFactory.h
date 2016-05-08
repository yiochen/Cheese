#pragma once
#include "entity/Entity.h"
#include "entity/attachment/Attachment.h"
namespace AttachmentFactory {
	//att means attachment
	Attachment* createHealAtt(Entity* entity);
	Attachment* createTargetAtt(Entity* entity);
	Attachment* createExplodeAtt(Entity* entity);
	Attachment* createSpawnAtt(Entity* entity);
}

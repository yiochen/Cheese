#pragma once
#include "entity/Entity.h"
#include "entity/attachment/Attachment.h"
namespace AttachmentFactory {
	Attachment* createHealAtt(Entity* entity);
	Attachment* createTargetAtt(Entity* entity);
	Attachment* createExplodeAtt(Entity* entity);
}

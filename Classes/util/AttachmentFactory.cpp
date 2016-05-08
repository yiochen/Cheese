#include "AttachmentFactory.h"
#include "common_include.h"
#include "world/World.h"

Attachment* createAttachment(Entity* entity) {
	Attachment* attachment =GET_WORLD->getAttPool()->New();//to be change to object pool
	attachment->initAttachment();
	entity->addAttachment(attachment);
	return attachment;
}

Attachment* AttachmentFactory::createHealAtt(Entity* entity) {
	//this method is required
	auto attachment = createAttachment(entity);
	attachment->concurrent = true;
	attachment->queueable = true;
	attachment->interruptable = false;
	attachment->setAnim("HEAL");
	
	return attachment;
}

Attachment* AttachmentFactory::createTargetAtt(Entity* entity) {
	auto attachment = createAttachment(entity);
	attachment->concurrent = true;
	attachment->queueable = true;
	attachment->interruptable = false;
	attachment->loop = 5;
	attachment->setAnim("TARGET");
	return attachment;
}

Attachment* AttachmentFactory::createExplodeAtt(Entity* entity) {
	auto attachment = createAttachment(entity);
	attachment->concurrent = true;
	attachment->queueable = true;
	attachment->interruptable = false;
	attachment->loop = 1;
	attachment->setAnim("EXPLODE");
	return attachment;
}

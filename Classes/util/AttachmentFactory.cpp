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
	attachment->setAnim(A_HEAL);
	
	return attachment;
}

Attachment* AttachmentFactory::createTargetAtt(Entity* entity) {
	auto attachment = createAttachment(entity);
	attachment->concurrent = true;
	attachment->queueable = true;
	attachment->interruptable = false;
	attachment->loop = 5;
	attachment->setAnim(A_TARGET);
	return attachment;
}

Attachment* AttachmentFactory::createExplodeAtt(Entity* entity) {
	auto attachment = createAttachment(entity);
	attachment->concurrent = true;
	attachment->queueable = true;
	attachment->interruptable = false;
	attachment->setAnim(A_SPIT_HIT);
	return attachment;
}

Attachment* AttachmentFactory::createSpawnAtt(Entity* entity) {
	auto attachment = createAttachment(entity);
	attachment->concurrent = false;
	attachment->queueable = false;
	attachment->interruptable = false;
	attachment->setAnim(A_SPAWN);
	return attachment;
}
Attachment* AttachmentFactory::createAttackBoostAtt(Entity* entity) {
	auto attachment = createAttachment(entity);
	attachment->concurrent = true;
	attachment->queueable = true;
	attachment->interruptable = true;
	attachment->setAnim(A_POWER_ATTACK);
	attachment->loop = 10;//TODO:: this is set to 10 right now. It should be loaded from lua file
	return attachment;
}
Attachment* AttachmentFactory::createSpeedBoostAtt(Entity* entity) {
	auto attachment = createAttachment(entity);
	attachment->concurrent = true;
	attachment->queueable = true;
	attachment->interruptable = true;
	attachment->setAnim(A_POWER_SPEED);
	attachment->loop = 10;//TODO:: this is set to 10 right now. It should be loaded from lua file
	return attachment;
}
Attachment* AttachmentFactory::createBloodAtt(Entity* entity) {
	auto attachment = createAttachment(entity);
	attachment->concurrent = true;
	attachment->queueable = true;
	attachment->interruptable = false;
	attachment->setAnim(A_BLOOD);
	attachment->loop = 1;//TODO:: this is set to 10 right now. It should be loaded from lua file
	return attachment;
}
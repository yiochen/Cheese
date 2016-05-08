#include "AttachmentAnimRunner.h"
#include "entity/player/Player.h"
#include "entity/zombie/Zombie.h"
#include "entity/attachment/Attachment.h"
#include "world/World.h"
#include "common_include.h"
AttachmentAnimRunner::AttachmentAnimRunner() {
    
}

void AttachmentAnimRunner::update(float delta) {
	//iterate over all entities, and update their attachment list
	World* world = GET_WORLD;
	//player
	auto playerIt = world->playerList.begin();
	while (playerIt != world->playerList.end()) {
		updateEntity(*playerIt, delta);
		playerIt++;
	}

	//zombie
	auto zombieIt = world->zombieList.begin();
	while (zombieIt != world->zombieList.end()) {
		updateEntity(*zombieIt, delta);
		zombieIt++;
	}

	//item
	auto itemIt = world->itemList.begin();
	while (itemIt != world->itemList.end()) {
		updateEntity(*itemIt, delta);
		itemIt++;
	}
}

void AttachmentAnimRunner::updateEntity(Entity* entity, float delta) {
	if (!entity) {
		CCLOG("ERROR::in attachmentAnimRunner, entity NULL");
		return;
	}
	//if entity is not null;

	//if the entity currently has anything playing or is playing concurrent attachment;
	bool isFree = true;
	auto attIt = entity->attachments.begin();
	while (attIt != entity->attachments.end()) {
		Attachment* att = (Attachment*)(*attIt);
		
		if (att) {
			if (att->finished) {
				entity->sprite->removeChild(att, true);
				//recycle the attachment
				attIt = entity->attachments.erase(attIt);
				GET_WORLD->getAttPool()->Delete(att);
			}
			else {
				if (att->isStarted && !att->concurrent) {
					//the entity is already playing something non concurent
					isFree = false;
				}
				else if ((!att->isStarted) && (att->concurrent || isFree)) {
					
					//add the attachment to sprite
					if (entity->sprite) {
						entity->sprite->addChild(att);
						att->play();
					}
					
					if (!att->concurrent) {
						//if not concurrent, set isFree to false
						isFree = false;
					}
				}
				attIt++;
			}
		}
		else {
			//the current pointer is null, erase it
			CCLOG("ERROR:: null in attachment iterator in AttachmentAnimRunner");
			attIt = entity->attachments.erase(attIt);
		}
	}
}
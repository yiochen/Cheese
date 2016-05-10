#include "ItemHelper.h"
#include "entity/Item/ItemCatalog.h"
#include "component/pooled/PowerUpComp.h"
#include "component/ComponentCatalog.h"
#include "util/AttachmentFactory.h"
void item_helper::getItem(Player* player, PowerUpComp* power) {
	if (!player || !power) {
		CCLOG("ERROR::in itemhelper, player or power NULL");
	}
	switch (power->type) {
	case ITEM_CA::ITEM_ATTACK:
		getAttackBoost(player);
		break;
	case ITEM_CA::ITEM_SPEED:
		getSpeedBoost(player);
		break;
	case ITEM_CA::ITEM_HEALTH:
		getHealth(player);
		break;
	case ITEM_CA::ITEM_INVIN:
		getInvin(player);
		break;
	}
}
void resetPlayerPower(Player* player) {
	if (player) {
		auto power = (PowerUpComp*)player->components[COMP_CA::POWER_UP_COMP];
		if (power) {
			power->type = ITEM_CA::ITEM_NONE;
		}
	}
}
void item_helper::removeItem(Player* player) {
	if (player) {
		auto power = (PowerUpComp*)player->components[COMP_CA::POWER_UP_COMP];
		if (power) {
			CCLOG("Removing %d", power->type);
			
			switch (power->type) {
			case ITEM_CA::ITEM_ATTACK:
				removeAttackBoost(player);
				power->type = ITEM_CA::ITEM_NONE;
				break;
			case ITEM_CA::ITEM_SPEED:
				removeSpeedBoost(player);
				power->type = ITEM_CA::ITEM_NONE;
				break;
			case ITEM_CA::ITEM_INVIN:
				removeInvin(player);
				power->type = ITEM_CA::ITEM_NONE;
				break;
			}
		}
	}
}


//this is a local helper function for giving continuing effect on player
void getContinuingEffect(Player* player, ITEM_CA type) {
	//if the player currently has something that is not NONE, remove the thing
	if (player) {
		auto power = (PowerUpComp*)player->components[COMP_CA::POWER_UP_COMP];
		if (power && power->type != ITEM_CA::ITEM_NONE) {
			//the player has something! remove it
			CCLOG("Player currently has something, remove it");
			item_helper::removeItem(player);
		}
		power->type = type;
	}
}
void item_helper::getHealth(Player* player) {

}



void item_helper::getAttackBoost(Player* player) {
	getContinuingEffect(player, ITEM_CA::ITEM_ATTACK);
	AttachmentFactory::createAttackBoostAtt(player);
}
void item_helper::getSpeedBoost(Player* player) {
	getContinuingEffect(player, ITEM_CA::ITEM_SPEED);
	AttachmentFactory::createSpeedBoostAtt(player);

}
void item_helper::getInvin(Player* player) {
	getContinuingEffect(player, ITEM_CA::ITEM_INVIN);
	AttachmentFactory::createInvincibilityAtt(player);
}



void item_helper::removeAttackBoost(Player* player) {
	player->removeAttachment(A_POWER_ATTACK);
}
void item_helper::removeSpeedBoost(Player* player) {
	player->removeAttachment(A_POWER_SPEED);
}
void item_helper::removeInvin(Player* player) {
	player->removeAttachment(A_POWER_SHIELD);
}
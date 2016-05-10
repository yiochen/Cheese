#include "PickUpRunner.h"
#include "entity/player/Player.h"
#include "entity/Item/Item.h"
#include "entity/Item/ItemCatalog.h"
#include "world/World.h"
#include "component/pooled/PowerUpComp.h"
#include "component/pooled/KineticComp.h"
#include "component/pooled/CombatComp.h"
#include "component/pooled/DomainComp.h"

PickUpRunner::PickUpRunner() {
    
}

void PickUpRunner::update(float delta) {
	//iterate over the players
	auto world = GET_WORLD;
	auto playerIt = world->playerList.begin();
	while (playerIt != world->playerList.end()) {
		updateEntity(*playerIt, delta);
		playerIt++;
	}
}

void PickUpRunner::updateEntity(Player* player, float delta) {
	World* world = GET_WORLD;
	if (player) {
		//see if the player can pick up stuff
		PowerUpComp* power = (PowerUpComp*)player->components[COMP_CA::POWER_UP_COMP];
		KineticComp* kin = (KineticComp*)player->components[COMP_CA::KINETIC_COMP];
		CombatComp*  combat = (CombatComp*)player->components[COMP_CA::COMBAT_COMP];
		if (power && kin && !player->marked
			//&& combat //for now, we dont check combat, because players dont have. TODO::add combat to player
			) {
			//iterate over the powerups
			auto itemIt = world->itemList.begin();
			while (itemIt != world->itemList.end()) {
				Item* item = (Item*)(*itemIt);
				if (item && !item->marked) {
					//get all the items 
					auto itemKin = (KineticComp*)item->components[COMP_CA::KINETIC_COMP];
					auto itemDom = (DomainComp*)item->components[COMP_CA::DOMAIN_COMP];
					auto itemPow = (PowerUpComp*)item->components[COMP_CA::POWER_UP_COMP];
					if (itemKin && itemDom && itemPow) {
						if (itemDom->contains(itemKin->pos, kin->pos)//player touches the item
							) {
							if (itemPow->instant) {
								//apply the instant power up
							}
							else {
								//replace player's powerup

							}
							//item already picked up, remove it from the playlist
							//it will be removed from the itemlist in AnimRunner because it's marked
							item->marked = true;
							item->sprite->removeFromParentAndCleanup(true);
							item->sprite = NULL;
						}
					}
				}
				itemIt++;
			}

		}

	}
}
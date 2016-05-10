
#include "EscapeRunner.h"
#include "component/pooled/HordeStatusComp.h"
EscapeRunner::EscapeRunner() {

}
void EscapeRunner::update(float delta) {
	//iterate over all the zombies, if it's has no player, and overlap with a player with recruit comp, recruit it.
	World* world = World::instance();
	auto playerIt = world->playerList.begin();
	while (playerIt != world->playerList.end()) {
		updateEntity(*playerIt, delta);
		playerIt++;
	}

}
void EscapeRunner::updateEntity(Player* player, float delta) {
	World* world = World::instance();
	if (player && world->swiss) {
		
		HordeStatusComp* horde = (HordeStatusComp*)player->components[COMP_CA::HORDE_STATUS_COMP];
		HordeStatusComp* swissHorde = (HordeStatusComp*)world->swiss->components[COMP_CA::HORDE_STATUS_COMP];
		if (horde&& horde->total == 0) {
			//remove from parent
			swissHorde->pointsRemaining++;
			player->sprite->removeFromParentAndCleanup(true);
			player->sprite = NULL;
			player->marked = true;
			
	//		player->cleanup();
	//		World* world = World::instance();
	//		world->playerList.remove(player);
		}
	}
}
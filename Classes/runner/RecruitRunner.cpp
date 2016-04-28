#include "RecruitRunner.h"
#include "world/World.h"
#include "component/basic/RecruitComp.h"
#include "component/pooled/DomainComp.h"
#include "component/pooled/KineticComp.h"
RecruitRunner::RecruitRunner() {
    
}

void RecruitRunner::update(float delta) {
	//iterate over all the zombies, if it's has no player, and overlap with a player with recruit comp, recruit it.
	World* world = World::instance();
	auto zombieIt = world->zombieList.begin();
	while (zombieIt != world->zombieList.end()) {
		updateEntity(*zombieIt,delta);
		zombieIt++;
	}
	
}
void RecruitRunner::updateEntity(Zombie* zombie, float delta) {
	if (zombie) {
		if (NULL == zombie->player) {
			//the zombie is a stray zombie, find a player
			auto kin = (KineticComp*)zombie->components[COMP_CA::KINETIC_COMP];
			if (kin == NULL) {
				CCLOG("zombie doesn't have kinetic comp");
				return;
			}
			World* world = World::instance();
			auto playerIt = world->playerList.begin();
			while (playerIt != world->playerList.end()) {
				Player* player = (Player*)(*playerIt);
				if (player) {
					RecruitComp* recruit = (RecruitComp*)player->components[COMP_CA::RECRUIT_COMP];
					KineticComp* playerKin = (KineticComp*)player->components[COMP_CA::KINETIC_COMP];
					DomainComp* domain = (DomainComp*)player->components[COMP_CA::DOMAIN_COMP];
					if (recruit) {
						if (!playerKin) CCLOG("dont have kin");
						if (!domain) CCLOG("dont have domain");
						CCLOG("domain is %f", domain->radius);
					}
					if (recruit && playerKin && domain && domain->contains(playerKin->pos, kin->pos)) {
						//recruit
						recruit->recruit(player, zombie);
						CCLOG("player successfully recruite a zombie!!");
						return;
					}
				}
				playerIt++;
			}
		}
		else {
			return;
		}
	}
}
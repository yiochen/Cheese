#pragma once
#include "entity/zombie/Zombie.h"
#include "entity/player/Player.h"

namespace zombie_stat_helper {
	Zombie* applyStat(Player* player, Zombie* zombie);
	Player* getZombieStatsFromLua(Player* player);
	
}
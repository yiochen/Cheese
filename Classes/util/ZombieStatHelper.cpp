#include "ZombieStatHelper.h"
#include "device/LuaDevice.h"
#include "luacppinterface.h"
#include "component/pooled/HordeStatusComp.h"
#include "component/pooled/CombatComp.h"
#include "component/pooled/ActionFlagComp.h"
#include "cocos2d.h"

USING_NS_CC;

Zombie* zombie_stat_helper::applyStat(Player* player, Zombie* zombie) {
	zombie->color = player->getColor();
	zombie->tint();
	zombie->alliance = player->alliance;
	auto hordeStatus = (HordeStatusComp*)
		player->components[COMP_CA::HORDE_STATUS_COMP];
	auto combat = (CombatComp*)zombie->components[COMP_CA::COMBAT_COMP];
	auto actionFlag = (ActionFlagComp*)zombie->components[COMP_CA::ACTION_FLAG_COMP];
	if (hordeStatus) {
		CCLOG("Applying stat to zombie of type %d, level %d", (int)zombie->category, hordeStatus[zombie->category]);
		ZStat stat = hordeStatus->zombieStats[zombie->category];
		if (combat) {
			combat->hp = stat.hp;
			combat->damage = stat.attack;
		}
		else {
			CCLOG("ERROR: zombie doesnt have combat");
		}
		if (actionFlag) {
			actionFlag->interval = stat.attackSpeed;
		}
		else {
			CCLOG("ERROR: zombie doenst have actionFlag");
		}
	}
	return zombie;
}

Player* zombie_stat_helper::getZombieStatsFromLua(Player* player) {
	auto lua = LuaDevice::instance();
	auto statFunc = lua->global().Get<LuaFunction<LuaTable(int, int)>>("zStatByLevel");
	auto hordeStatus = (HordeStatusComp*)player->components[COMP_CA::HORDE_STATUS_COMP];
	if (hordeStatus) {
		CCLOG("getting stats from lua");
		for (int i = ZOMBIE_CA::ZOMBIE_START + 1; i < ZOMBIE_CA::ZOMBIE_END; i++) {
			auto statTable = statFunc.Invoke(i, hordeStatus->zombieLvs[(ZOMBIE_CA)i]);
			hordeStatus->zombieStats[(ZOMBIE_CA)i].attack = statTable.Get<int>("attack");
			hordeStatus->zombieStats[(ZOMBIE_CA)i].hp = statTable.Get<int>("hp");
			hordeStatus->zombieStats[(ZOMBIE_CA)i].attackSpeed = statTable.Get<int>("attackSpeed");
		}
	}
	return player;
}

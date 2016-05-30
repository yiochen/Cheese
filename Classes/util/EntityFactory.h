#pragma once
#include"world/world_include.h"
#include "world/World.h"
#include "device/LuaDevice.h"
#include "luacppinterface.h"
#include "entity/Item/ItemCatalog.h"

/*this class contain some helper static methods for creating entities in the game. 
Note that the entity created is not added to to world or renderlist yet.*/
namespace EntityFactory {

	void initEntity(Entity* entity, LuaTable& luaTable);
	Zombie* createZombie(Player* player,LuaFunction<LuaTable()>& luaFunc);
	Zombie* createStrayZombie(ZOMBIE_CA);
	Player* createPlayer(bool isHuman,bool isBoss, float gameTime);

	Player* playerFromLua(LuaTable& table);
	Zombie* zombieFromLua(Player* player, LuaTable& table);
	
	Item* createBullet(Entity* user, Vec2 destination);
	Item* createPickUp(ITEM_CA type, Vec2 location);
}

#pragma once
#include"world/world_include.h"
#include "world/World.h"
#include "device/LuaDevice.h"
#include "luacppinterface.h"


/*this class contain some helper static methods for creating entities in the game. 
Note that the entity created is not added to to world or renderlist yet.*/
namespace EntityFactory {

	void initEntity(Entity* entity, LuaTable& luaTable);
	Zombie* createZombie(Player* player,LuaFunction<LuaTable()>& luaFunc);
	Zombie* createStrayZombie(ZOMBIE_CA);
	Player* createPlayer(bool isHuman);
	Item* createBullet(Entity* user, Vec2 destination);
	
};

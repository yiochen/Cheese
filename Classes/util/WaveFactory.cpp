#include "WaveFactory.h"
#include "EntityFactory.h"
void WaveFactory::loadWave(GAME_MODE mode, int waveIndex) {
	World* world =World::instance();
	LuaDevice* lua = LuaDevice::instance();
	LuaTable waveTable=lua->global().Get<LuaFunction<LuaTable(int)>>("getWave").Invoke(waveIndex);
	LuaTable playerList = waveTable.Get<LuaTable>("playerList");
	int pTotal = playerList.Get<int>("count");
	for (int i = 0; i < pTotal; i++) {
		LuaTable playerTable = playerList.Get<LuaTable>(i);
		Player* player = EntityFactory::playerFromLua(playerTable);
		LuaTable zombieList = playerTable.Get<LuaTable>("zombieList");
		int zTotal = zombieList.Get<int>("count");
		for (int j = 0; j < zTotal; j++) {
			LuaTable zombieTable = zombieList.Get<LuaTable>(j);
			EntityFactory::zombieFromLua(player,zombieTable);
		}
	}
}
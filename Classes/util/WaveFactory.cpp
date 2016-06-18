#include "WaveFactory.h"
#include "EntityFactory.h"
/*Return 0 when there loading wave failed (already loaded the last wave), otherwise, return the time */
float WaveFactory::loadWave(GAME_MODE mode, int level, int waveIndex) {
	World* world =World::instance();
	LuaDevice* lua = LuaDevice::instance();
	LuaTable waveTable=lua->global().Get<LuaFunction<LuaTable(int)>>("getWave").Invoke(waveIndex);
	int category = waveTable.Get<int>("category");
	CCLOG("Wave status is %d", category);
	if (category == WAVE_CA::NONE) { return 0; }
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
	return waveTable.Get<float>("maxTime");

}
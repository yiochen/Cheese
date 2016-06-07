#pragma once
#include "world/world_include.h"
#include "world/World.h"
#include "device/LuaDevice.h"
#include "luacppinterface.h"

namespace WaveFactory {
	void loadWave(GAME_MODE mode, int level, int waveIndex);
}
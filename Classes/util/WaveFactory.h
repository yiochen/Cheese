#pragma once
#include "world/world_include.h"
#include "world/World.h"
#include "device/LuaDevice.h"
#include "luacppinterface.h"
enum WAVE_CA {
	PREP,NORMAL,FINAL, NONE
};
namespace WaveFactory {
	float loadWave(GAME_MODE mode, int level, int waveIndex);
}
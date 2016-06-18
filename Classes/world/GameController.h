#pragma once
//GameController controls the process of game. It handles wave creation, difficulty calculation, etc.
//It updates the model (World)

#include "world/World.h"
#include "world/world_include.h"
#include "world/GameMode.h"
class GameController {
private:
	GameController();
	static GameController* s_instance;
	float timer;
	bool isTimerRunning;
	float endTime;
	bool requestingWave;
	float nextWaveTime;
public:
	static GameController* instance() {
		if (s_instance == nullptr) {
			s_instance = new GameController();
			s_instance->init();
		}
		return s_instance;
	}
	bool quitFlag;
	GAME_MODE mode;
	int level;
	int wave;
	void init();
	float getTime() { return timer; }
	void resetTimer() { timer = 0.9f; }
	void incTimer(float diff) { timer += diff; }
	void startGame(GAME_MODE mode, int level);
	bool nextWave();
	
	void quitGame();
	void update(float dt);
	void destroy();
};

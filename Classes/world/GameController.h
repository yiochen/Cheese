#pragma once
//GameController controls the process of game. It handles wave creation, difficulty calculation, etc.
//It updates the model (World)

#include "world/World.h"
#include "world/world_include.h"

class GameController {
private:
	GameController();
	static GameController* s_instance;
	
	float timer;
public:
	static GameController* instance() {
		if (s_instance == nullptr) {
			s_instance = new GameController();
			s_instance->init();
		}
		return s_instance;
	}
	bool quitFlag;
	void init();
	float getTime() { return timer; }
	void resetTimer() { timer = 0.9f; }
	void incTimer(float diff) { timer += diff; }
	void startGame(GAME_MODE mode, int level);
	void quitGame();
	void update(float dt);
	void destroy();
};

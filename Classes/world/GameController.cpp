#include "GameController.h"
#include "cocos2d.h"
#include "util/WaveFactory.h"
USING_NS_CC;
GameController* GameController::s_instance = nullptr;

GameController::GameController() {
    
}

void GameController::init() {
	//initialize world;
	World* world = World::instance();
	quitFlag = false;
	mode = GAME_MODE::ENDLESS;
	level = 0;
	wave = 0;
}

void GameController::startGame(GAME_MODE mode, int level) {
	World* world = World::instance();
	world->initWorldData(mode, level);
	wave = 0;
	WaveFactory::loadWave(mode, level, wave);
}
void GameController::nextWave() {
	wave += 1;
	WaveFactory::loadWave(mode, level, wave);
}
void GameController::quitGame() {
	quitFlag = true;
}

void GameController::update(float dt) {
	World* world = World::instance();
	if (world) {
		if (world->destroyFlag) {
			world->destroyData();
			world->destroyFlag = false;
			CCLOG("next level");
		}
		else {
			world->update(dt);
		}
	}
}

void GameController::destroy() {
	World::instance()->destroy();
}
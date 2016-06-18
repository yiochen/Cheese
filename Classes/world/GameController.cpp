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
	isTimerRunning = false;
	endTime = 0;
	requestingWave = false;
}
/* Start a level */
void GameController::startGame(GAME_MODE mode, int level) {
	World* world = World::instance();
	world->initWorldData(mode, level);
	this->wave = -1;
	this->timer = 0;
	this->requestingWave = true;
}

bool GameController::nextWave() {
	this->wave++;
	float waveMaxTime = WaveFactory::loadWave(this->mode, this->level, this->wave);
	if (waveMaxTime == 0) {
		CCLOG("cannot load wave or got to the end of wave, mode is %d, level %d, wave %d", int(this->mode), this->level, this->wave);
		//cannot load wave
		this->nextWaveTime = -1;
		return false;
	}
	else {
		this->nextWaveTime = this->timer + waveMaxTime;
		return true;
	}
}
void GameController::quitGame() {
	quitFlag = true;
}

void GameController::update(float dt) {
	timer += dt;
	World* world = World::instance();
	if (world) {
		if (world->destroyFlag) {
			world->destroyData();
			world->destroyFlag = false;
			CCLOG("next level");
		}
		else {
			if (this->nextWaveTime>0 && timer > this->nextWaveTime) {
				this->requestingWave = true;
			}
			if (requestingWave) {
				this->nextWave();
				requestingWave = false;
			}

			world->update(dt);
		}
	}
}

void GameController::destroy() {
	World::instance()->destroy();
}
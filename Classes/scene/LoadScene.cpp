#include "LoadScene.h"
#include "scene/GameScene.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "world/World.h"

#include "device/LuaDevice.h"
#include "world/Config.h"

#include "util/AudioDir.h"
USING_NS_CC;
using namespace cocostudio::timeline;
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

Scene* LoadScene::createScene() {
	auto scene = Scene::create();
	auto layer = LoadScene::create();
	scene->addChild(layer);
	return scene;
}

bool LoadScene::init() {
	if (!Layer::init()) {
		return false;
	}
	auto rootNode = CSLoader::createNode("LoadScene.csb");
	addChild(rootNode);
	this->scheduleOnce(schedule_selector(LoadScene::preload), 0.5f);
}

void LoadScene::preload(float dt) {
	//do all the loading
	//load 
	CCLOG("start creating lua device");
	LuaDevice* lua = LuaDevice::instance();
	CCLOG("initializing lua device");
	lua->init();
	CCLOG("loading all the lua file");
	lua->loadAll();
	Config* config = Config::instance();
	config->init();

	//load music
	auto audio = SimpleAudioEngine::getInstance();
	audio->stopBackgroundMusic();
	audio->preloadBackgroundMusic(S_GAME);
	audio->preloadEffect(S_CHUCKER_ATTACK);
	audio->preloadEffect(S_CHUCKER_IMPACT);
	audio->preloadEffect(S_HEALER_ATTACK);
	audio->preloadEffect(S_PLAYER_DEATH);
	audio->preloadEffect(S_SLAPPER_ATTACK);
	audio->preloadEffect(S_ZOMBIE_DEATH);
	CCLOG("finish loading");
	transit(0.0f);
}
void LoadScene::transit(float dt) {
	auto gameScene = GameScene::createScene();
	Director::getInstance()->replaceScene(gameScene);
}
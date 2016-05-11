#include "scene/GameScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "world/World.h"
#include "Debug.h"
#include "scene/ArmyTabScene.h"
#include "scene/HelpScene.h"
#include "scene/GameOverScene.h"

#include "device/LuaDevice.h"
#include "world/Config.h"
#include "SimpleAudioEngine.h"

#include "util/CheatSystem.h"
#include "util/AudioDir.h"
USING_NS_CC;
using namespace CocosDenshion;

Scene* GameScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto rootNode = CSLoader::createNode("GameScene.csb");
	addChild(rootNode);

	cocos2d::ui::Button* armyBtn = (cocos2d::ui::Button*) rootNode->getChildByName("HudLayer")->getChildByName("ArmyButton");
	armyBtn->addTouchEventListener(CC_CALLBACK_2(GameScene::armyBtnTouchEvent, this));
	cocos2d::ui::Button* helpBtn = (cocos2d::ui::Button*) rootNode->getChildByName("HudLayer")->getChildByName("HelpButton");
	helpBtn->addTouchEventListener(CC_CALLBACK_2(GameScene::helpBtnTouchEvent, this));
	cocos2d::ui::Button* exitBtn = (cocos2d::ui::Button*) rootNode->getChildByName("HudLayer")->getChildByName("ExitButton");
	exitBtn->addTouchEventListener(CC_CALLBACK_2(GameScene::exitBtnTouchEvent, this));
	cocos2d::ui::Text* informationPanel = (rootNode->getChildByName("HudLayer")->getChildByName<cocos2d::ui::Text*>("Information"));
	informationPanel->setString("i cant manipulate this without gameScene isntance?");//you should be able to. World is technically a local field of game scene. It can manipulate anything in game scene as long as you pass a reference to it.

	Node* backgroundLayer=(Node*)rootNode->getChildByName("MapLayer");
	Node* actionLayer = (Node*)rootNode->getChildByName("ActionLayer");
	Node* hudLayer = (Node*)rootNode->getChildByName("HudLayer");
	EventListenerKeyboard *keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	keyListener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyListener, this);

	//create world and initialize world
	//To be moved to a loading scene
	
	LuaDevice* lua = LuaDevice::instance();
	
	Config* config = Config::instance();
	config->WORLD_HEIGHT = this->getContentSize().height;
	config->WORLD_WIDTH = this->getContentSize().width;
	CCLOG("the size of the world is %f,%f", config->WORLD_WIDTH, config->WORLD_HEIGHT);
	World * world = World::instance();
	world->initWorld(backgroundLayer,actionLayer, hudLayer);
	//test lua
	//TODO:to be deleted
	
	//load sound
	auto audio = SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic(S_GAME, true);
	this->scheduleUpdate();
	//this->resume();
	return true;
}

void GameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event) {

	auto world = World::instance();
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		world->keyStatus[GameKey::UP] = true;
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		world->keyStatus[GameKey::DOWN] = true;
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		world->keyStatus[GameKey::LEFT] = true;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		world->keyStatus[GameKey::RIGHT] = true;
		break;
	}
}
void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event) {
	auto world = World::instance();
	switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
			world->keyStatus[GameKey::UP] = false;
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW: 
			world->keyStatus[GameKey::DOWN] = false;
			break;
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW: 
			world->keyStatus[GameKey::LEFT] = false;
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW: 
			world->keyStatus[GameKey::RIGHT] = false;
			break;
		case EventKeyboard::KeyCode::KEY_H: {
			auto helpTab = HelpScene::createScene();
			Director::getInstance()->pushScene((Scene*)helpTab);
			break;
		}
		case EventKeyboard::KeyCode::KEY_U: {
			auto armyTab = ArmyTabScene::createScene();
			Director::getInstance()->pushScene((Scene*)armyTab);
			break;
		}
		case EventKeyboard::KeyCode::KEY_C: {
			//cheat key, kill a zombe from the zombie list 
			cheat_system::killOneZombie();
			break;
		}
		case EventKeyboard::KeyCode::KEY_L: {
			cheat_system::launchBullet();
			break;
		}
	}
}

void GameScene::armyBtnTouchEvent(Ref *sender, cocos2d::ui::Widget::TouchEventType type) {
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
		//time to transit to the game scene;
		auto armyTab = ArmyTabScene::createScene();
		Director::getInstance()->pushScene((Scene*)armyTab);
	}
}
void GameScene::helpBtnTouchEvent(Ref *sender, cocos2d::ui::Widget::TouchEventType type) {
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
		//time to transit to the game scene;
		auto helpTab = HelpScene::createScene();
		Director::getInstance()->pushScene((Scene*)helpTab);
	}
}
void GameScene::exitBtnTouchEvent(Ref *sender, cocos2d::ui::Widget::TouchEventType type) {
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
		//time to transit to the game scene;
		// NEED TO DO MORE HANDLE DESTRUCTORS HERE, END GAME AND LEVEL
		Director::getInstance()->popScene();
	}
}


void GameScene::update(float delta) {
	//TODO: for some reason, this is not called
	World* world = World::instance();
	if (world) {
		world->update(delta);
		if (world->destroyFlag) {
			world->destroy();
			world->destroyFlag = false;
			auto gameOverScene = GameOverScene::createScene();
			
			Director::getInstance()->replaceScene(gameOverScene);
			
		}
	}

}
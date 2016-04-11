#include "scene/GameScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "world/World.h"
#include "Debug.h"
#include "scene/ArmyTabScene.h"
#include "scene/HelpScene.h"
USING_NS_CC;



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
	
	



	Node* backgroundLayer=(Node*)rootNode->getChildByName("MapLayer");
	Node* actionLayer = (Node*)rootNode->getChildByName("ActionLayer");
	EventListenerKeyboard *keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	keyListener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyListener, this);

	//create world and initialize world
	World * world = World::instance();
	world->initWorld(backgroundLayer,actionLayer);
	world->initSpriteCache();
	this->resume();
	return true;
}

void GameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event) {
	CCLOG("Key with keycode %d pressed", keyCode);
}
void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event) {
	CCLOG("Key with keycode %d released", keyCode);
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
	World* world = World::instance();
	if (world) {
		world->update(delta);
	}
}
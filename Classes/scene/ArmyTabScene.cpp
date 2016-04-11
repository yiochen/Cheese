#include "scene/ArmyTabScene.h"
#include "cocostudio/CocoStudio.h"

#include "GameScene.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* ArmyTabScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = ArmyTabScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool ArmyTabScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto rootNode = CSLoader::createNode("ArmyTab.csb");
	/*
	cocos2d::ui::Button* startBtn = (cocos2d::ui::Button*) rootNode->getChildByName("btn_start");
	startBtn->addTouchEventListener(CC_CALLBACK_2(ArmyTab::startBtnTouchEvent, this));
	addChild(rootNode);
	*/

	addChild(rootNode);
	return true;
}

void ArmyTabScene::startBtnTouchEvent(Ref *sender, cocos2d::ui::Widget::TouchEventType type) {
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
		//time to transit to the game scene;
		auto gameScene = GameScene::createScene();
		Director::getInstance()->replaceScene((Scene*)gameScene);
	}
}
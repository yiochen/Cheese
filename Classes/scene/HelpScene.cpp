#include "scene/HelpScene.h"
#include "cocostudio/CocoStudio.h"

#include "GameScene.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelpScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = HelpScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelpScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto rootNode = CSLoader::createNode("HelpScene.csb");

	cocos2d::ui::Button* exitBtn = (cocos2d::ui::Button*) rootNode->getChildByName("ExitBtn");
	exitBtn->addTouchEventListener(CC_CALLBACK_2(HelpScene::ExitBtnTouchEvent, this));



	addChild(rootNode);
	return true;
}

void HelpScene::ExitBtnTouchEvent(Ref *sender, cocos2d::ui::Widget::TouchEventType type) {
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
		//time to transit to the game scene;
		Director::getInstance()->popScene();
	}
}
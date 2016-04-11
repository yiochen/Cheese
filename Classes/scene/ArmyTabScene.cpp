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
	
	cocos2d::ui::Button* exitBtn = (cocos2d::ui::Button*) rootNode->getChildByName("ExitBtn");
	exitBtn->addTouchEventListener(CC_CALLBACK_2(ArmyTabScene::ExitBtnTouchEvent, this));

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(ArmyTabScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	cocos2d::ui::Button* stinkiesTabBtn = (cocos2d::ui::Button*) rootNode->getChildByName("ArmyCount")->getChildByName("TheStinkies");
	stinkiesTabBtn->addTouchEventListener(CC_CALLBACK_2(ArmyTabScene::StinkiesBtnTouchEvent, this, rootNode));
	cocos2d::ui::Button* HolyBonesTabBtn = (cocos2d::ui::Button*) rootNode->getChildByName("ArmyCount")->getChildByName("HolyBones");
	HolyBonesTabBtn->addTouchEventListener(CC_CALLBACK_2(ArmyTabScene::HolyBtnTouchEvent, this, rootNode));
	cocos2d::ui::Button* ChuckersTabBtn = (cocos2d::ui::Button*) rootNode->getChildByName("ArmyCount")->getChildByName("Chuckers");
	ChuckersTabBtn->addTouchEventListener(CC_CALLBACK_2(ArmyTabScene::ChuckersBtnTouchEvent, this, rootNode));
	rootNode->getChildByName("StatStinkies")->setVisible(false);
	rootNode->getChildByName("StatHolyBones")->setVisible(false);
	rootNode->getChildByName("StatChuckers")->setVisible(false);

	

	addChild(rootNode);
	return true;
}

void ArmyTabScene::ExitBtnTouchEvent(Ref *sender, cocos2d::ui::Widget::TouchEventType type) {
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
		//time to transit to the game scene;
		Director::getInstance()->popScene();
	}
}
void ArmyTabScene::StinkiesBtnTouchEvent(Ref *sender, cocos2d::ui::Widget::TouchEventType type, cocos2d::Node* root) {
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
		//time to transit to the game scene;
		root->getChildByName("StatStinkies")->setVisible(true);
		root->getChildByName("StatHolyBones")->setVisible(false);
		root->getChildByName("StatChuckers")->setVisible(false);
	}
}

void ArmyTabScene:: HolyBtnTouchEvent(Ref *sender, cocos2d::ui::Widget::TouchEventType type, cocos2d::Node* root) {
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
		//time to transit to the game scene;
		root->getChildByName("StatStinkies")->setVisible(false);
		root->getChildByName("StatHolyBones")->setVisible(true);
		root->getChildByName("StatChuckers")->setVisible(false);
	}
}

void ArmyTabScene::ChuckersBtnTouchEvent(Ref *sender, cocos2d::ui::Widget::TouchEventType type, cocos2d::Node* root) {
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
		//time to transit to the game scene;
		root->getChildByName("StatStinkies")->setVisible(false);
		root->getChildByName("StatHolyBones")->setVisible(false);
		root->getChildByName("StatChuckers")->setVisible(true);
	}
}
void ArmyTabScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event) {
	switch (keyCode) {

	case EventKeyboard::KeyCode::KEY_ESCAPE: {
		CCLOG("PRESSED ESCAPE");
		Director::getInstance()->popScene();
		break;
	}
	}
}
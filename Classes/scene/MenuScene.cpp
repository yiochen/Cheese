#include "scene/MenuScene.h"
#include "cocostudio/CocoStudio.h"

#include "GameScene.h"
#include "box/BoxHelper.h"
USING_NS_CC;

using namespace cocostudio::timeline;

Scene* MenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MenuScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("MenuScene.csb");
	cocos2d::ui::Button* startBtn =(cocos2d::ui::Button*) rootNode->getChildByName("btn_start");
	startBtn->addTouchEventListener(CC_CALLBACK_2(MenuScene::startBtnTouchEvent, this));
    addChild(rootNode);

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(MenuScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	this->scheduleUpdate();
	boxHelper.initBox2d();

    return true;
}

void MenuScene::startBtnTouchEvent(Ref *sender, cocos2d::ui::Widget::TouchEventType type) {
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
		//time to transit to the game scene;
		auto gameScene = GameScene::createScene();
		Director::getInstance()->pushScene((Scene*)gameScene);
		
	}
}

void MenuScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event) {
	switch (keyCode) {

	case EventKeyboard::KeyCode::KEY_ESCAPE: {
		exit;
		break;
	}
	case EventKeyboard::KeyCode::KEY_ENTER: {
		auto gameScene = GameScene::createScene();
		Director::getInstance()->pushScene((Scene*)gameScene);
		break;
	}
	}
}

void MenuScene::update(float delta) {

}
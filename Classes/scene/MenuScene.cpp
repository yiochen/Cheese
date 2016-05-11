#include "scene/MenuScene.h"
#include "cocostudio/CocoStudio.h"
#include "scene/LoadScene.h"

#include "box/BoxHelper.h"
#include "SimpleAudioEngine.h"
#include "util/AudioDir.h"
using namespace CocosDenshion;
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
	cocos2d::ui::Button* exitBtn = (cocos2d::ui::Button*) rootNode->getChildByName("btn_exit_game");
	exitBtn->addTouchEventListener(CC_CALLBACK_2(MenuScene::exitBtnTouchEvent, this));
    addChild(rootNode);

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(MenuScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	this->scheduleUpdate();
	auto layerSize = this->getContentSize();
	boxHelper.setSize(layerSize.width, layerSize.height);
	boxHelper.initBox2d();
	//load the spirte;
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(MenuScene::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	auto audio = SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic(S_MENU,true);


	

    return true;
}

void MenuScene::startBtnTouchEvent(Ref *sender, cocos2d::ui::Widget::TouchEventType type) {
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
		//time to transit to the game scene;
		auto loadScene = LoadScene::createScene();
		Director::getInstance()->pushScene((Scene*)loadScene);
		
	}
}
void MenuScene::exitBtnTouchEvent(Ref *sender, cocos2d::ui::Widget::TouchEventType type) {
		if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
			Director::getInstance()->end();
		}
}
void MenuScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event) {
	switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_ESCAPE: {
			exit;
			break;
		}
		case EventKeyboard::KeyCode::KEY_ENTER: {
			auto loadScene = LoadScene::createScene();
			Director::getInstance()->pushScene((Scene*)loadScene);
			break;
		}
	}
}

void MenuScene::update(float delta) {
	boxHelper.update(delta);
	//update all the bodies in the body list
	auto it = bodyList.begin();
	while (it != bodyList.end()) {
		b2Body* body = (b2Body*)(*it);
		Sprite* sp = (Sprite*)(body->GetUserData());
		//CCLOG("the box's position is %f, %f", body->GetPosition().x*boxHelper.S2W, body->GetPosition().y*boxHelper.S2W);
		sp->setPosition(body->GetPosition().x*boxHelper.W2S, body->GetPosition().y*boxHelper.W2S);
		float R2D = 180.0f / 3.14159f;
		sp->setRotation(-body->GetAngle()*R2D);
		it++;
	}
}
bool MenuScene::onTouchBegan(Touch* touch, Event* e) {
	auto pos = touch->getLocation();
	createCheese(pos.x, pos.y);
	CCLOG("touched %f, %f", pos.x, pos.y);
	return true;
}
void MenuScene::createCheese(float mouseX, float mouseY) {
	auto layerSize = this->getContentSize();
	float halfWidth = layerSize.width;
	float halfHeight = layerSize.height;
	//create a new Sprite
	Sprite* sp = Sprite::create("Assets/Images/cheese.png");
	sp->setPosition(Vec2(mouseX, mouseY));
	
	addChild(sp);
	float S2W = boxHelper.S2W;
	float W2S = boxHelper.W2S;
	bodyList.push_back(boxHelper.createDynamicRect(mouseX*S2W, mouseY*S2W, 260.0f*S2W, 160.0f*S2W, sp));
}
#include "GameOverScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include <iostream>
USING_NS_CC;
using namespace cocostudio::timeline;

Scene* GameOverScene::createScene() {
	auto scene = Scene::create();
	auto layer = GameOverScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameOverScene::init() {
	if (!Layer::init())
	{
		return false;
	}

	auto rootNode = CSLoader::createNode("GameOverScene.csb");

	addChild(rootNode);
	this->scheduleOnce(schedule_selector(GameOverScene::transit), 1.0f);
	//this->getChildByName<cocos2d::ui::Text*>("score_text")->setText("You got 2 points");
	//
	return true;
}

void GameOverScene::transit(float dt) {
	Director::getInstance()->popScene();

}
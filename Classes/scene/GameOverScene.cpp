#include "GameOverScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include <iostream>
#include <sstream>
#include "world/World.h"
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
	cocos2d::ui::Text* scoreText=rootNode->getChildByName<cocos2d::ui::Text*>("score_text");
	if (scoreText) {
		std::stringstream s;
		s << "You got " << World::instance()->score << " points!";
		scoreText->setString(s.str().c_str());
	}
	addChild(rootNode);
	this->scheduleOnce(schedule_selector(GameOverScene::transit), 1.0f);
	
	//
	return true;
}

void GameOverScene::transit(float dt) {
	Director::getInstance()->popScene();

}
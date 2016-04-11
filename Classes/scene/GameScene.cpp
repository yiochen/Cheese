#include "scene/GameScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "world/World.h"
#include "Debug.h"
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
	
	Node* backgroundLayer=(Node*)rootNode->getChildByName("desert_layer");
	Node* actionLayer = (Node*)rootNode->getChildByName("action_layer");
	EventListenerKeyboard *keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	keyListener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyListener, this);

	//create world and initialize world
	World * world = World::instance();
	world->initWorld(backgroundLayer,actionLayer);
	this->resume();
	return true;
}

void GameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event) {
	CCLOG("Key with keycode %d pressed", keyCode);
}
void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event) {
	CCLOG("Key with keycode %d released", keyCode);
}

void GameScene::update(float delta) {
	World* world = World::instance();
	if (world) {
		world->update(delta);
	}
}
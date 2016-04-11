#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

class GameScene : public Layer {
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(GameScene);

	void update(float) override;

private:
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event);

	void GameScene::exitBtnTouchEvent(Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void GameScene::armyBtnTouchEvent(Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void GameScene::helpBtnTouchEvent(Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	
};

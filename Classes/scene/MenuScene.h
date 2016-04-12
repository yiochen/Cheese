#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "box/BoxHelper.h"
#include <list>


USING_NS_CC;

class MenuScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
	void MenuScene::update(float delta);
    // implement the "static create()" method manually
    CREATE_FUNC(MenuScene);
private:
	BoxHelper boxHelper;
	void startBtnTouchEvent(Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void MenuScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event);
	std::list<b2Body*> bodyList;
	void createCheese(float mouseX, float mouseY);
	bool onTouchBegan(Touch*, Event*);
};

#endif // __HELLOWORLD_SCENE_H__


#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

class ArmyTabScene : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(ArmyTabScene);
private:
	void ExitBtnTouchEvent(Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void ArmyTabScene::StinkiesBtnTouchEvent(Ref *sender, cocos2d::ui::Widget::TouchEventType type, cocos2d::Node* root);
	void ArmyTabScene::HolyBtnTouchEvent(Ref *sender, cocos2d::ui::Widget::TouchEventType type, cocos2d::Node* root);
	void ArmyTabScene::ChuckersBtnTouchEvent(Ref *sender, cocos2d::ui::Widget::TouchEventType type, cocos2d::Node* root);
	void ArmyTabScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event);
};

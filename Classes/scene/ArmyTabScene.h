
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "entity/zombie/ZombieStatCatalog.h"
#include "world/World.h"
#include "component/pooled/HordeStatusComp.h"

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
	void ArmyTabScene::StinkieHP(Ref *sender, cocos2d::ui::Widget::TouchEventType type, cocos2d::Node* root);
	void ArmyTabScene::StinkieAttack(Ref *sender, cocos2d::ui::Widget::TouchEventType type, cocos2d::Node* root);
	void ArmyTabScene::StinkieAttackSpeed(Ref *sender, cocos2d::ui::Widget::TouchEventType type, cocos2d::Node* root);
	void ArmyTabScene::ChuckerHP(Ref *sender, cocos2d::ui::Widget::TouchEventType type, cocos2d::Node* root);
	void ArmyTabScene::ChuckerAttack(Ref *sender, cocos2d::ui::Widget::TouchEventType type, cocos2d::Node* root);
	void ArmyTabScene::ChuckerAttackSpeed(Ref *sender, cocos2d::ui::Widget::TouchEventType type, cocos2d::Node* root);
	void ArmyTabScene::ChuckerRange(Ref *sender, cocos2d::ui::Widget::TouchEventType type, cocos2d::Node* root);
	void ArmyTabScene::HolyBoneHP(Ref *sender, cocos2d::ui::Widget::TouchEventType type, cocos2d::Node* root);
	void ArmyTabScene::HolyBoneAttack(Ref *sender, cocos2d::ui::Widget::TouchEventType type, cocos2d::Node* root);
	void ArmyTabScene::HolyBoneAttackSpeed(Ref *sender, cocos2d::ui::Widget::TouchEventType type, cocos2d::Node* root);

	void ArmyTabScene::StatBtnTouchEvent(ZOMBIE_STAT_CA A,cocos2d::Node* root);

};

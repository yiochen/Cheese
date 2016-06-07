#include "scene/ArmyTabScene.h"
#include "cocostudio/CocoStudio.h"
#include "component/pooled/HordeStatusComp.h"
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

	//text labels
	World* world = World::instance();
	Player* swiss = world->gamerList.front();
	HordeStatusComp* hordeStatusComp = (HordeStatusComp*)swiss->components[COMP_CA::HORDE_STATUS_COMP];
	(rootNode->getChildByName("StatStinkies")->getChildByName("StatPanel")->getChildByName<cocos2d::ui::Text*>("currentHealth"))->setString(std::to_string((int)hordeStatusComp->zombieStat[ZOMBIE_STAT_CA::STINKIE_HP]));
	(rootNode->getChildByName("StatStinkies")->getChildByName("StatPanel")->getChildByName<cocos2d::ui::Text*>("currentAttack"))->setString(std::to_string((int)hordeStatusComp->zombieStat[ZOMBIE_STAT_CA::STINKIE_ATTACK]));
	(rootNode->getChildByName("StatStinkies")->getChildByName("StatPanel")->getChildByName<cocos2d::ui::Text*>("currentAttackSpeed"))->setString((std::to_string(hordeStatusComp->zombieStat[ZOMBIE_STAT_CA::STINKIE_ATTACKSPEED])).substr(0,3));

	(rootNode->getChildByName("StatChuckers")->getChildByName("StatPanel")->getChildByName<cocos2d::ui::Text*>("currentHealth"))->setString(std::to_string((int)hordeStatusComp->zombieStat[ZOMBIE_STAT_CA::CHUCKER_HP]));
	(rootNode->getChildByName("StatChuckers")->getChildByName("StatPanel")->getChildByName<cocos2d::ui::Text*>("currentAttack"))->setString(std::to_string((int)hordeStatusComp->zombieStat[ZOMBIE_STAT_CA::CHUCKER_ATTACK]));
	(rootNode->getChildByName("StatChuckers")->getChildByName("StatPanel")->getChildByName<cocos2d::ui::Text*>("currentAttackSpeed"))->setString((std::to_string(hordeStatusComp->zombieStat[ZOMBIE_STAT_CA::CHUCKER_ATTACKSPEED])).substr(0, 3));
	(rootNode->getChildByName("StatChuckers")->getChildByName("StatPanel")->getChildByName<cocos2d::ui::Text*>("currentRange"))->setString(std::to_string((int)hordeStatusComp->zombieStat[ZOMBIE_STAT_CA::CHUCKER_RANGE]));

	(rootNode->getChildByName("StatHolyBones")->getChildByName("StatPanel")->getChildByName<cocos2d::ui::Text*>("currentAttackSpeed"))->setString((std::to_string(hordeStatusComp->zombieStat[ZOMBIE_STAT_CA::HOLY_BONE_ATTACK_SPEED])).substr(0, 3));
	(rootNode->getChildByName("StatHolyBones")->getChildByName("StatPanel")->getChildByName<cocos2d::ui::Text*>("currentAttack"))->setString(std::to_string((int)hordeStatusComp->zombieStat[ZOMBIE_STAT_CA::HOLY_BONE_HEAL]));
	(rootNode->getChildByName("StatHolyBones")->getChildByName("StatPanel")->getChildByName<cocos2d::ui::Text*>("currentHealth"))->setString(std::to_string((int)hordeStatusComp->zombieStat[ZOMBIE_STAT_CA::HOLY_BONE_HP]));

	(rootNode->getChildByName("StatHolyBones")->getChildByName("StatPanel")->getChildByName<cocos2d::ui::Text*>("pointsRemaining"))->setString(std::to_string((int)hordeStatusComp->pointsRemaining));
	(rootNode->getChildByName("StatStinkies")->getChildByName("StatPanel")->getChildByName<cocos2d::ui::Text*>("pointsRemaining"))->setString(std::to_string((int)hordeStatusComp->pointsRemaining));
	(rootNode->getChildByName("StatChuckers")->getChildByName("StatPanel")->getChildByName<cocos2d::ui::Text*>("pointsRemaining"))->setString(std::to_string((int)hordeStatusComp->pointsRemaining));


	//buttons
	cocos2d::ui::Button* stinkiesHealthPlus = (cocos2d::ui::Button*) rootNode->getChildByName("StatStinkies")->getChildByName("StatPanel")->getChildByName("HealthPlus");
	stinkiesHealthPlus->addTouchEventListener(CC_CALLBACK_2(ArmyTabScene::StinkieHP, this, rootNode));
	cocos2d::ui::Button* stinkiesAttackPlus = (cocos2d::ui::Button*) rootNode->getChildByName("StatStinkies")->getChildByName("StatPanel")->getChildByName("AttackPlus");
	stinkiesAttackPlus->addTouchEventListener(CC_CALLBACK_2(ArmyTabScene::StinkieAttack, this, rootNode));
	cocos2d::ui::Button* stinkiesAttackspeedPlus = (cocos2d::ui::Button*) rootNode->getChildByName("StatStinkies")->getChildByName("StatPanel")->getChildByName("AttackSpeedPlus");
	stinkiesAttackspeedPlus->addTouchEventListener(CC_CALLBACK_2(ArmyTabScene::StinkieAttackSpeed, this, rootNode));
	
	cocos2d::ui::Button* chuckersHealthPlus = (cocos2d::ui::Button*) rootNode->getChildByName("StatChuckers")->getChildByName("StatPanel")->getChildByName("HealthPlus");
	chuckersHealthPlus->addTouchEventListener(CC_CALLBACK_2(ArmyTabScene::ChuckerHP, this, rootNode));
	cocos2d::ui::Button* chuckersAttackPlus = (cocos2d::ui::Button*) rootNode->getChildByName("StatChuckers")->getChildByName("StatPanel")->getChildByName("AttackPlus");
	chuckersAttackPlus->addTouchEventListener(CC_CALLBACK_2(ArmyTabScene::ChuckerAttack, this, rootNode));
	cocos2d::ui::Button* chuckersAttackspeedPlus = (cocos2d::ui::Button*) rootNode->getChildByName("StatChuckers")->getChildByName("StatPanel")->getChildByName("AttackSpeedPlus");
	chuckersAttackspeedPlus->addTouchEventListener(CC_CALLBACK_2(ArmyTabScene::ChuckerAttackSpeed, this, rootNode));
	cocos2d::ui::Button* chuckersRangePlus = (cocos2d::ui::Button*) rootNode->getChildByName("StatChuckers")->getChildByName("StatPanel")->getChildByName("CurrentRangePlus");
	chuckersRangePlus->addTouchEventListener(CC_CALLBACK_2(ArmyTabScene::ChuckerRange, this, rootNode));

	cocos2d::ui::Button* holyBonesHealthPlus = (cocos2d::ui::Button*) rootNode->getChildByName("StatHolyBones")->getChildByName("StatPanel")->getChildByName("HealthPlus");
	holyBonesHealthPlus->addTouchEventListener(CC_CALLBACK_2(ArmyTabScene::HolyBoneHP, this, rootNode));
	cocos2d::ui::Button* holyBonesHealPlus = (cocos2d::ui::Button*) rootNode->getChildByName("StatHolyBones")->getChildByName("StatPanel")->getChildByName("AttackPlus");
	holyBonesHealPlus->addTouchEventListener(CC_CALLBACK_2(ArmyTabScene::HolyBoneAttack, this, rootNode));
	cocos2d::ui::Button* holyBonesAttackspeedPlus = (cocos2d::ui::Button*) rootNode->getChildByName("StatHolyBones")->getChildByName("StatPanel")->getChildByName("AttackSpeedPlus");
	holyBonesAttackspeedPlus->addTouchEventListener(CC_CALLBACK_2(ArmyTabScene::HolyBoneAttackSpeed, this, rootNode));

	
	addChild(rootNode);
	return true;
}
void ArmyTabScene::StinkieHP(Ref *sender, cocos2d::ui::Widget::TouchEventType type, cocos2d::Node* root) {
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
		StatBtnTouchEvent(ZOMBIE_STAT_CA::STINKIE_HP, root);
	}
}
void ArmyTabScene::StinkieAttack(Ref *sender, cocos2d::ui::Widget::TouchEventType type, cocos2d::Node* root) {
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
		StatBtnTouchEvent(ZOMBIE_STAT_CA::STINKIE_ATTACK, root);
	}
}
void ArmyTabScene::StinkieAttackSpeed(Ref *sender, cocos2d::ui::Widget::TouchEventType type, cocos2d::Node* root) {
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
		StatBtnTouchEvent(ZOMBIE_STAT_CA::STINKIE_ATTACKSPEED, root);
	}
}
void ArmyTabScene::ChuckerHP(Ref *sender, cocos2d::ui::Widget::TouchEventType type, cocos2d::Node* root) {
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
		StatBtnTouchEvent(ZOMBIE_STAT_CA::CHUCKER_HP, root);
	}
}
void ArmyTabScene::ChuckerAttack(Ref *sender, cocos2d::ui::Widget::TouchEventType type, cocos2d::Node* root) {
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
		StatBtnTouchEvent(ZOMBIE_STAT_CA::CHUCKER_ATTACK, root);
	}
}
void ArmyTabScene::ChuckerAttackSpeed(Ref *sender, cocos2d::ui::Widget::TouchEventType type, cocos2d::Node* root) {
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
		StatBtnTouchEvent(ZOMBIE_STAT_CA::CHUCKER_ATTACKSPEED, root);
	}
}
void ArmyTabScene::ChuckerRange(Ref *sender, cocos2d::ui::Widget::TouchEventType type, cocos2d::Node* root) {
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
		StatBtnTouchEvent(ZOMBIE_STAT_CA::CHUCKER_RANGE, root);
	}
}
void ArmyTabScene::HolyBoneHP(Ref *sender, cocos2d::ui::Widget::TouchEventType type, cocos2d::Node* root) {
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
		StatBtnTouchEvent(ZOMBIE_STAT_CA::HOLY_BONE_HP, root);
	}
}
void ArmyTabScene::HolyBoneAttack(Ref *sender, cocos2d::ui::Widget::TouchEventType type, cocos2d::Node* root) {
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
		StatBtnTouchEvent(ZOMBIE_STAT_CA::HOLY_BONE_HEAL, root);
	}
}
void ArmyTabScene::HolyBoneAttackSpeed(Ref *sender, cocos2d::ui::Widget::TouchEventType type, cocos2d::Node* root) {
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
		StatBtnTouchEvent(ZOMBIE_STAT_CA::HOLY_BONE_ATTACK_SPEED, root);
	}
}


void ArmyTabScene::StatBtnTouchEvent( ZOMBIE_STAT_CA a,cocos2d::Node* root) {
	// stats 1/2/3/4   helth/attack/attackspeed/range/       in healer zombie case, attack = heal, atksped = heal speed
		World* world = World::instance();
		HordeStatusComp* hordeStatusComp = (HordeStatusComp*)world->gamerList.front()->components[COMP_CA::HORDE_STATUS_COMP];
		if (hordeStatusComp->pointsRemaining > 0) {
			if (a == ZOMBIE_STAT_CA::CHUCKER_HP || a == ZOMBIE_STAT_CA::STINKIE_HP || a == ZOMBIE_STAT_CA::HOLY_BONE_HP) {
				hordeStatusComp->zombieStat[a] += 3;
			}
			if (a == ZOMBIE_STAT_CA::CHUCKER_ATTACKSPEED || a == ZOMBIE_STAT_CA::STINKIE_ATTACKSPEED || a == ZOMBIE_STAT_CA::HOLY_BONE_ATTACK_SPEED) {
				if (a == ZOMBIE_STAT_CA::CHUCKER_ATTACKSPEED && hordeStatusComp->zombieStat[ZOMBIE_STAT_CA::CHUCKER_ATTACKSPEED] >= .4) {
					hordeStatusComp->zombieStat[a] -= .2;
				}
				else if (a == ZOMBIE_STAT_CA::STINKIE_ATTACKSPEED && hordeStatusComp->zombieStat[ZOMBIE_STAT_CA::STINKIE_ATTACKSPEED] >= .4) {
					hordeStatusComp->zombieStat[a] -= .2;
				}
				else if (a == ZOMBIE_STAT_CA::HOLY_BONE_ATTACK_SPEED && hordeStatusComp->zombieStat[ZOMBIE_STAT_CA::HOLY_BONE_ATTACK_SPEED] >= .4) {
					hordeStatusComp->zombieStat[a] -= .2;
				}
				else {
					hordeStatusComp->pointsRemaining += 1;
				}

			}
			if (a == ZOMBIE_STAT_CA::CHUCKER_RANGE || a == ZOMBIE_STAT_CA::STINKIE_RANGE || a == ZOMBIE_STAT_CA::HOLY_BONE_RANGE) {
				hordeStatusComp->zombieStat[a] += 50;
			}
			if (a == ZOMBIE_STAT_CA::CHUCKER_ATTACK || a == ZOMBIE_STAT_CA::STINKIE_ATTACK || a == ZOMBIE_STAT_CA::HOLY_BONE_HEAL) {
				hordeStatusComp->zombieStat[a] += 1;
			}
			CCLOG("Stat is updated to %lf", hordeStatusComp->zombieStat[a]);
			hordeStatusComp->pointsRemaining -= 1;
			(root->getChildByName("StatStinkies")->getChildByName("StatPanel")->getChildByName<cocos2d::ui::Text*>("currentHealth"))->setString(std::to_string((int)hordeStatusComp->zombieStat[ZOMBIE_STAT_CA::STINKIE_HP]));
			(root->getChildByName("StatStinkies")->getChildByName("StatPanel")->getChildByName<cocos2d::ui::Text*>("currentAttack"))->setString(std::to_string((int)hordeStatusComp->zombieStat[ZOMBIE_STAT_CA::STINKIE_ATTACK]));
			(root->getChildByName("StatStinkies")->getChildByName("StatPanel")->getChildByName<cocos2d::ui::Text*>("currentAttackSpeed"))->setString((std::to_string(hordeStatusComp->zombieStat[ZOMBIE_STAT_CA::STINKIE_ATTACKSPEED])).substr(0, 3));

			(root->getChildByName("StatChuckers")->getChildByName("StatPanel")->getChildByName<cocos2d::ui::Text*>("currentHealth"))->setString(std::to_string((int)hordeStatusComp->zombieStat[ZOMBIE_STAT_CA::CHUCKER_HP]));
			(root->getChildByName("StatChuckers")->getChildByName("StatPanel")->getChildByName<cocos2d::ui::Text*>("currentAttack"))->setString(std::to_string((int)hordeStatusComp->zombieStat[ZOMBIE_STAT_CA::CHUCKER_ATTACK]));
			(root->getChildByName("StatChuckers")->getChildByName("StatPanel")->getChildByName<cocos2d::ui::Text*>("currentAttackSpeed"))->setString((std::to_string(hordeStatusComp->zombieStat[ZOMBIE_STAT_CA::CHUCKER_ATTACKSPEED])).substr(0, 3));
			(root->getChildByName("StatChuckers")->getChildByName("StatPanel")->getChildByName<cocos2d::ui::Text*>("currentRange"))->setString(std::to_string((int)hordeStatusComp->zombieStat[ZOMBIE_STAT_CA::CHUCKER_RANGE]));

			(root->getChildByName("StatHolyBones")->getChildByName("StatPanel")->getChildByName<cocos2d::ui::Text*>("currentAttackSpeed"))->setString((std::to_string(hordeStatusComp->zombieStat[ZOMBIE_STAT_CA::HOLY_BONE_ATTACK_SPEED])).substr(0, 3));
			(root->getChildByName("StatHolyBones")->getChildByName("StatPanel")->getChildByName<cocos2d::ui::Text*>("currentAttack"))->setString(std::to_string((int)hordeStatusComp->zombieStat[ZOMBIE_STAT_CA::HOLY_BONE_HEAL]));
			(root->getChildByName("StatHolyBones")->getChildByName("StatPanel")->getChildByName<cocos2d::ui::Text*>("currentHealth"))->setString(std::to_string((int)hordeStatusComp->zombieStat[ZOMBIE_STAT_CA::HOLY_BONE_HP]));

			(root->getChildByName("StatHolyBones")->getChildByName("StatPanel")->getChildByName<cocos2d::ui::Text*>("pointsRemaining"))->setString(std::to_string((int)hordeStatusComp->pointsRemaining));
			(root->getChildByName("StatStinkies")->getChildByName("StatPanel")->getChildByName<cocos2d::ui::Text*>("pointsRemaining"))->setString(std::to_string((int)hordeStatusComp->pointsRemaining));
			(root->getChildByName("StatChuckers")->getChildByName("StatPanel")->getChildByName<cocos2d::ui::Text*>("pointsRemaining"))->setString(std::to_string((int)hordeStatusComp->pointsRemaining));
			hordeStatusComp->updateHorde();
			CCLOG("The hp of hordestatus is now %d ", (int)hordeStatusComp->zombieStat[ZOMBIE_STAT_CA::STINKIE_HP]);
		}

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
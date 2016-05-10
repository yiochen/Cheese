#include "InformationPanel.h"
#include "world/World.h"

#include "cocostudio/CocoStudio.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

InformationPanel::InformationPanel() {
	gameTimeStr = "Game Time: 0";
	pointsStr = "Score: 0";
	zombieRemainingStr = "Zombies Remaining: 5";
	finalStr = gameTimeStr + pointsStr + zombieRemainingStr;

};



void InformationPanel::setFinalStr() {
	finalStr = gameTimeStr + "\n" + pointsStr + "\n" + zombieRemainingStr;
	World* world = World::instance();
	cocos2d::ui::Text* informationPanel = (cocos2d::ui::Text*)(world->getHUDNode()->getChildByName("Information"));
	informationPanel->setString(finalStr);

}
void InformationPanel::setGameTimeStr(float sec) {
	gameTimeStr = "Game Time: " + std::to_string(((int)sec / 60)) + ":" + std::to_string(((int)sec % 60));
	setFinalStr();
}
void InformationPanel::updateTime() {
	World* world = World::instance();
	setGameTimeStr(world->spawningPool->totalTime);
}

void InformationPanel::setZombieRemainingStr(int x) {
	zombieRemainingStr = "Zombies Remaining: " + std::to_string(x);
	updateTime();
}
void InformationPanel::setPointsStr(int x) {
	pointsStr = "Score: " + std::to_string(x);
	updateTime();
}
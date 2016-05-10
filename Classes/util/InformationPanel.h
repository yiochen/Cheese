#pragma once
#include "cocos2d.h"


/*RESPONSIBLE FOR the string display in HUD layer of game scene
*/
class InformationPanel {

public:
	std::string gameTimeStr, pointsStr, zombieRemainingStr, finalStr;
	InformationPanel();
	void setFinalStr();
	void setGameTimeStr(float sec);
	void setZombieRemainingStr(int);
	void setPointsStr(int);
	void updateTime();
};
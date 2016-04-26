#include "ZombieSensorComp.h"

ZombieSensorComp::ZombieSensorComp() {
    
}

void ZombieSensorComp::init() {
	this->clean();
}

void ZombieSensorComp::clean() {
	this->closestAlliance = NULL;
	this->closestEnemy = NULL;
	this->allianceDis.set(LARGE_NUM, LARGE_NUM);
	this->enermyDis.set(LARGE_NUM, LARGE_NUM);
}

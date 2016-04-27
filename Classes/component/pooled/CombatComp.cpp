#include "CombatComp.h"

CombatComp::CombatComp() {

}
void CombatComp::init() {
	this->hp = 0;
	this->pendingDmg = 0;
	this->isDying = false;
	this->isDead = false;
}
void CombatComp::setHP(int HP) {
	hp = HP;
}
void CombatComp::setDamage(int ATTACK) {
	damage = ATTACK;
}

void CombatComp::setAttackSpeed(float atkspd) {
	attackSpeed = atkspd;
}
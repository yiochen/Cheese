#include "CombatComp.h"

CombatComp::CombatComp() {

}
void CombatComp::init() {
	this->pendingDmg = 0;
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
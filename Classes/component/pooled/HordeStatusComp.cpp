#include "HordeStatusComp.h"

HordeStatusComp::HordeStatusComp() {
    
}

void HordeStatusComp::init() {
	this->sumPos.setZero();
	this->total = 0;
	for (int i = ZOMBIE_CA::ZOMBIE_START; i < ZOMBIE_CA::ZOMBIE_END; i++) {
		this->zombieCounts[(ZOMBIE_CA)i] = 0;
	}
}

void HordeStatusComp::zeroPos() {
	this->sumPos.setZero();
}
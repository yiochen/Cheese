#pragma once
#include "component/CompHeader.h"
#include "entity/player/Player.h"
#include "entity/zombie/Zombie.h"

class RecruitComp :public Comp{
private:
	void brainwash(Player* self, Zombie* target);
public:
    RecruitComp();
	void recruit(Player* self, Zombie * target);
	
};

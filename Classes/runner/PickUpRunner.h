#pragma once
#include "runner/EntityRunner.h"
#include "entity/player/Player.h"
/*This runner is for character to pick up items*/
class PickUpRunner :public EntityRunner{
private:
	//Only player can pick up items
	void updateEntity(Player* player, float delta);
public:
    PickUpRunner();
	void update(float delta) override;

};

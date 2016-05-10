#pragma once
#include "component/CompHeader.h"
#include "entity/Item/ItemCatalog.h"
/*Component used by items to mark what kind of powerup it is.
This is also used by player to mark if the player can pick up item. Or the item he has right now.
Power up can be interrupted. which means if you pick up something while still possessing something, it will be changed to the new thing.Unless the powerup is instant*/
class PowerUpComp :public PooledComp{
public:
    PowerUpComp();
	void init() override;
	ITEM_CA type;
	bool instant;//instant items can be consumed right away and do not have any long term effect on the character, for example, health.
};

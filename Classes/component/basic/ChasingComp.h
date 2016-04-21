#pragma once
#include "component/CompHeader.h"
/*Entity with this behavior will be moving toward the target.
If the target has DomainComp, this component should lost effect. 
This entity is used as a mark and for Runners to recognize it.
It doesn't contain any personalized information*/
class ChasingComp:public Comp {
public:
    ChasingComp();
	/*Helper function to update the self's velocity based on the self and target's relative position,
	return true when reached destination, return false when it cannot chase or havent reach*/
	bool chase(Entity* self, Entity* target);
};

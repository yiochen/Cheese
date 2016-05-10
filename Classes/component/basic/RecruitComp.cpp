#include "RecruitComp.h"
#include "component/pooled/HordeStatusComp.h"
#include "component/pooled/CombatComp.h"
RecruitComp::RecruitComp() {
    
}

void RecruitComp::brainwash(Player* self, Zombie* target) {
	//update the hordestatus
	auto hordeStatus = (HordeStatusComp*)self->components[COMP_CA::HORDE_STATUS_COMP];
	if (hordeStatus) {
		hordeStatus->zombieCounts[target->catagory]++;
		hordeStatus->total++;
	}
	target->alliance = self->alliance;
	auto combatComp = (CombatComp*)target->components[COMP_CA::COMBAT_COMP];
	if (combatComp) {
		combatComp->alliance = target->alliance;
	}
	target->components[COMP_CA::WANDERING_COMP] = NULL;
	target->tint(self->getColor());
}

void RecruitComp::recruit(Player* self, Zombie* target) {
	if (self && target) {
		target->player = self;
		brainwash(self, target);
	}
}
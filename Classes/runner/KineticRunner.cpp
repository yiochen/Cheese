#include "KineticRunner.h"
#include "world/World.h"
#include "component/ComponentCatalog.h"
#include "entity/Entity.h"
#include "component/pooled/KineticComp.h"
#include <vector>

KineticRunner::KineticRunner() {

}

void KineticRunner::update(float delta) {


	//I know that only Swiss will be affected by keyboard input directly, so I just get Swiss
	auto keyStatus = World::instance()->keyStatus;
	auto swiss = World::instance()->swiss;

	KineticComp* kineticComp = (KineticComp*)(swiss->components[COMP_CA::KINETIC_COMP]);
	kineticComp->step(swiss);
}
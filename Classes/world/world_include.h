#pragma once
//include all the components and runners needed by World

//components
#include "component/basic/KeyboardComp.h"
#include "component/pooled/KineticComp.h"
#include "component/pooled/AnimComp.h"
#include "component/basic/ChasingComp.h"
#include "component/pooled/DomainComp.h"

//runners
#include "runner/KeyboardRunner.h"
#include "runner/KineticRunner.h"
#include "runner/AnimRunner.h"
#include "runner/ZombieFollowRunner.h"
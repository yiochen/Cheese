#pragma once
//include all the components and runners needed by World

//components
#include "component/basic/KeyboardComp.h"
#include "component/pooled/KineticComp.h"
#include "component/pooled/AnimComp.h"
#include "component/basic/ChasingComp.h"
#include "component/pooled/DomainComp.h"
#include "component/pooled/HordeStatusComp.h"
#include "component/pooled/CombatComp.h"
#include "component/pooled/HealComp.h"
#include "component/basic/SeperationComp.h"
#include "component/basic/FollowingComp.h"
#include "component/pooled/WanderingComp.h"
#include "component/pooled/ActionFlagComp.h"
#include "component/basic/MeleeAttackComp.h"
#include "component/pooled/ZombieSensorComp.h"
#include "component/basic/RecruitComp.h"
#include "component/pooled/TrajectComp.h"

//runners
#include "runner/KeyboardRunner.h"
#include "runner/KineticRunner.h"
#include "runner/AnimRunner.h"
#include "runner/ZombieFollowRunner.h"
#include "runner/ZombieTallyRunner.h"
#include "runner/ActionFlagRunner.h"
#include "runner/WandererRunner.h"
#include "runner/MeleeAttackRunner.h"
#include "runner/StatRunner.h"
#include "runner/RecruitRunner.h"
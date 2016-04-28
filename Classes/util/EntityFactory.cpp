#include "EntityFactory.h"
#include "world/World.h"
#include "ObjectPool/ObjectPool.h"
#include "cocos2d.h"
USING_NS_CC;


void EntityFactory::initEntity(Entity* entity, LuaTable& luaTable) {
	auto world = World::instance();
	CCLOG("init entities");
	//loading all the data
	//basic components
#define luabool(st) luaTable.Get<bool>(st)
#define luastring(st) LuaDevice::instance()->getString(luaTable.Get<std::string>(st))
#define luaint(st) luaTable.Get<int>(st)
#define luafloat(st) luaTable.Get<float>(st)
#define luazombfunc(st) luaTable.Get<LuaFunction<LuaTable()>>(st)
#define newcomp(type, enum) world->getCompPool<type>(enum)->New()
#define addcomp(enum, comp) entity->components[enum] = comp
	if (luabool("ChasingComp")) {
		//create chasing comp
		CCLOG("creating chasing comp");
		entity->components[COMP_CA::CHASING_COMP] = world->commonComps[COMP_CA::CHASING_COMP];
	}
	if (luabool("SeperationComp")) {
		CCLOG("creating seperation comp");
		entity->components[COMP_CA::SEPERATION_COMP] = world->commonComps[COMP_CA::SEPERATION_COMP];
	}
	if (luabool("FollowingComp")) {
		CCLOG("creating followingComp");
		entity->components[COMP_CA::FOLLOWING_COMP] = world->commonComps[COMP_CA::FOLLOWING_COMP];
	}
	if (luabool("MeleeAttackComp")) {
		CCLOG("creating meleeAttackComp");
		entity->components[COMP_CA::MELEE_ATTACK_COMP] = world->commonComps[COMP_CA::MELEE_ATTACK_COMP];
	}
	if (luabool("KeyboardComp")) {
		CCLOG("creating keyboardComp");
		entity->components[COMP_CA::KEYBOARD_COMP] = world->commonComps[COMP_CA::KEYBOARD_COMP];
	}

	//pooled component
	if (luabool("ActionFlagComp")) {
		CCLOG("creating actionflagComp");
		auto actionFlag = newcomp(ActionFlagComp, COMP_CA::ACTION_FLAG_COMP);
		actionFlag->init();
		actionFlag->interval = luafloat("attackSpeed");
		addcomp(COMP_CA::ACTION_FLAG_COMP, actionFlag);

	}
	if (luabool("AnimComp")) {
		CCLOG("creating anim comp");
		auto anim = newcomp(AnimComp, COMP_CA::ANIM_COMP);
		anim->init();
		anim->name=luastring("AnimCompName");
		CCLOG("anim comp name is %s", anim->name.c_str());
		anim->newAnimState = A_WALK_FORTH;
		addcomp(COMP_CA::ANIM_COMP, anim);
	}
	//if (luabool("CombatComp")) {
		CCLOG("creating combat comp");
		auto  combat = newcomp(CombatComp, COMP_CA::COMBAT_COMP);
		combat->init();
		combat->hp = luaint("hp");
		combat->damage = luaint("attack");
		//combat->attackSpeed = luafloat("attackSpeed");
		combat->alliance = luaint("alliance");//TODO: set alliance in lua file
		CCLOG("alliance is %d", combat->alliance);
		addcomp(COMP_CA::COMBAT_COMP, combat);
	//}
	if (luabool("DomainComp")) {
		CCLOG("creating domain comp");
		auto domain = newcomp(DomainComp, COMP_CA::DOMAIN_COMP);
		domain->init();
		domain->radius = luafloat("range");

		addcomp(COMP_CA::DOMAIN_COMP, domain);
	}
	if (luabool("HealComp")) {
		CCLOG("creating heal comp");
		auto heal = newcomp(HealComp, COMP_CA::HEAL_COMP);
		heal->init();
		heal->heal = luaint("heal");
		//heal->healSpeed = luafloat("attackSpeed");
		addcomp(COMP_CA::HEAL_COMP, heal);
	}
	if (luabool("HordeStatusComp")) {
		CCLOG("creating hordestatus comp");
		auto hordeStatus = newcomp(HordeStatusComp, COMP_CA::HORDE_STATUS_COMP);
		hordeStatus->init();
		hordeStatus->zombieCounts[ZOMBIE_CA::STINKIE] = luaint("StinkieNum");
		hordeStatus->zombieCounts[ZOMBIE_CA::CHUCKER] = luaint("ChuckerNum");
		hordeStatus->zombieCounts[ZOMBIE_CA::HOLY_BONE] = luaint("HolyBondNum");
		addcomp(COMP_CA::HORDE_STATUS_COMP, hordeStatus);
		
	}
	if (luabool("KineticComp")) {
		CCLOG("creating kinetic comp");
		auto kinetic = newcomp(KineticComp, COMP_CA::KINETIC_COMP);
		kinetic->init();
		kinetic->maxSpeed = luafloat("KineticCompMaxSpeed");
		auto x = luafloat("x");
		auto y = luafloat("y");
		CCLOG("the initial x and y is %f,%f", x, y);
		kinetic->pos.set(x, y);//TODO: zombie's position seems not working
		addcomp(COMP_CA::KINETIC_COMP, kinetic);
	}
	if (luabool("ZombieSensorComp")) {
		CCLOG("creating zombie sensor comp");
		
		
	}
	CCLOG("finish entity initialization");
}

Zombie* EntityFactory::createZombie(Player* player,LuaFunction<LuaTable()>& luaFunc) {
	World* world = World::instance();
	Zombie* zombie = world->getZombiePool()->New();
	zombie->init();
	zombie->player = player;
	
	auto luaTable = luaFunc.Invoke();
	initEntity(zombie,luaTable);
	zombie->catagory =(ZOMBIE_CA) luaint("ZombieCatagory");
	world->zombieList.push_back(zombie);
	return zombie;
}

Player* EntityFactory::createPlayer(bool isHuman) {
	World* world = World::instance();
	Player* player = world->getPlayerPool()->New();
	player->init();
	//load lua file, 
	auto lua = LuaDevice::instance();
	auto luaFunc = lua->global().Get<LuaFunction<LuaTable(bool)>>("createPlayer");
	auto luaTable =luaFunc.Invoke(isHuman);
	initEntity(player,luaTable);
	//create zombies for the player
	auto stinkieNum = luaint("StinkieNum");
	auto chuckerNum = luaint("ChuckerNum");
	auto holyNum = luaint("HolyBoneNum");

	auto stinkieFunc = luazombfunc("StinkieFunc");
	auto chuckerFunc = luazombfunc("ChuckerFunc");
	auto holyFunc = luazombfunc("HolyBoneFunc");

	for (int i = 0; i < stinkieNum; i++) {
		createZombie(player, stinkieFunc);
	}
	for (int i = 0; i < chuckerNum; i++) {
		createZombie(player, chuckerFunc);
	}
	for (int i = 0; i < holyNum; i++) {
		createZombie(player, holyFunc);
	}
	//add player to the world
	world->playerList.push_back(player);
	return player;
}

//	//TODO: createZombie and createPlayer should be combined when the lua function is ready
//	Zombie* createZombie(Player* player) {
//	LuaDevice* lua = LuaDevice::instance();
//
//
//	World* world = World::instance();
//	auto zombiePool = world->getZombiePool();
//	Zombie* zombie = zombiePool->New();
//	zombie->init();
//	zombie->player = player;
//	HordeStatusComp* hordeStatus = (HordeStatusComp*)player->components[COMP_CA::HORDE_STATUS_COMP];
//	hordeStatus->total++;
//	//kinetic Component
//	KineticComp* kineticComp = world->getCompPool<KineticComp>(COMP_CA::KINETIC_COMP)->New();
//	zombie->components[COMP_CA::KINETIC_COMP] = kineticComp;
//	kineticComp->maxSpeed = 100.0f + RandomHelper::random_real<float>(-20.0f, 20.0f);
//	//TODO kinetic position should be relative to the world;
//	kineticComp->pos.set(((KineticComp*)player->components[COMP_CA::KINETIC_COMP])->pos);
//	//kineticComp->pos.set(100, 100);
//	kineticComp->vel.set(0, 0);
//	//animation Component
//	AnimComp* animComp = world->getCompPool<AnimComp>(COMP_CA::ANIM_COMP)->New();
//	//following is to be read from a file
//
//	switch (RandomHelper::random_int(0, 2)) {
//	case 0:
//		animComp->name = "basic_zombie";
//		break;
//	case 1:
//		animComp->name = "chucker";
//		break;
//	case 2:
//		animComp->name = "healer";
//		break;
//	}
//
//	zombie->catagory = ZOMBIE_CA::STINKIE;
//	hordeStatus->zombieCounts[ZOMBIE_CA::STINKIE]++;
//	/*}
//	else {
//	animComp->name = "chucker";
//	zombie->catagory = ZOMBIE_CA::CHUCKER;
//	hordeStatus->zombieCounts[ZOMBIE_CA::CHUCKER]++;
//	}*/
//
//	animComp->newAnimState = A_WALK_FORTH;
//	zombie->components[COMP_CA::ANIM_COMP] = animComp;
//	//add chasingComp
//	zombie->components[COMP_CA::CHASING_COMP] = world->commonComps[COMP_CA::CHASING_COMP];
//	zombie->components[COMP_CA::SEPERATION_COMP] = world->commonComps[COMP_CA::SEPERATION_COMP];
//	zombie->components[COMP_CA::FOLLOWING_COMP] = world->commonComps[COMP_CA::FOLLOWING_COMP];
//	zombie->components[COMP_CA::MELEE_ATTACK_COMP] = world->commonComps[COMP_CA::MELEE_ATTACK_COMP];
//	CombatComp* combatComp = world->getCompPool<CombatComp>(COMP_CA::COMBAT_COMP)->New();
//	combatComp->init();
//	combatComp->setHP(100);
//	combatComp->setDamage(50);
//	//Don't do the following way. right now it is just testing
//	if (player == world->swiss) {//should not compare with swiss. Should be two seperated function for AI player and human player.
//		combatComp->alliance = 1;
//	}
//	else {
//		combatComp->alliance = 2;
//	}
//	zombie->components[COMP_CA::COMBAT_COMP] = combatComp;
//	DomainComp* domainComp = world->getCompPool<DomainComp>(COMP_CA::DOMAIN_COMP)->New();
//	domainComp->init();
//	domainComp->radius = 50.0f;
//	zombie->components[COMP_CA::DOMAIN_COMP] = domainComp;
//	ActionFlagComp* actionComp = world->getCompPool<ActionFlagComp>(COMP_CA::ACTION_FLAG_COMP)->New();
//	actionComp->init();
//	//testing actionComp
//	actionComp->interval = 3.0f;//3 second
//	zombie->components[COMP_CA::ACTION_FLAG_COMP] = actionComp;
//
//	return zombie;
//}
//Player * createPlayer(bool isHuman) {
//	World* world = World::instance();
//	auto pool = world->getPlayerPool();
//	auto player = pool->New();
//
//	//read lua here
//
//	player->init();
//	//keyboard Component
//
//
//	//kinetic Component
//	KineticComp* kineticComp = world->getCompPool<KineticComp>(COMP_CA::KINETIC_COMP)->New();
//	player->components[COMP_CA::KINETIC_COMP] = kineticComp;
//	kineticComp->maxSpeed = 100.0f;
//	//TODO kinetic position should be relative to the world;
//	if (isHuman) {
//		player->components[COMP_CA::KEYBOARD_COMP] = world->commonComps[COMP_CA::KEYBOARD_COMP];
//		kineticComp->pos.set(500, 100);
//		kineticComp->vel.set(0, 0);
//	}
//
//	if (!isHuman) {
//		kineticComp->pos.set(500, 500);
//
//	}
//
//	//animation Component
//	AnimComp* animComp = world->getCompPool<AnimComp>(COMP_CA::ANIM_COMP)->New();
//	//following is to be read from a file
//	animComp->name = "swiss";
//	animComp->newAnimState = A_WALK_FORTH;
//	player->components[COMP_CA::ANIM_COMP] = animComp;
//	DomainComp* domainComp = world->getCompPool<DomainComp>(COMP_CA::DOMAIN_COMP)->New();
//	player->components[COMP_CA::DOMAIN_COMP] = domainComp;
//	domainComp->radius = 50;//set the radius of domain to 50 for now. TODO: to be changed to read from lua
//	HordeStatusComp* hordeStatus = world->getCompPool<HordeStatusComp>(COMP_CA::HORDE_STATUS_COMP)->New();
//	hordeStatus->init();
//	player->components[COMP_CA::HORDE_STATUS_COMP] = hordeStatus;
//
//
//
//	return player;
//}
//

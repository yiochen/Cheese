#include "EntityFactory.h"
#include "world/World.h"
#include "ObjectPool/ObjectPool.h"
#include "cocos2d.h"
#include "entity/zombie/ZombieStatCatalog.h"
#include "util/AttachmentFactory.h"
USING_NS_CC;


void EntityFactory::initEntity(Entity* entity, LuaTable& luaTable) {
	auto world = World::instance();
//	CCLOG("init entities");
	//loading all the data
	//basic components
#define luabool(st) luaTable.Get<bool>(st)
#define luastring(st) LuaDevice::instance()->getString(luaTable.Get<std::string>(st))
#define luaint(st) luaTable.Get<int>(st)
#define luafloat(st) luaTable.Get<float>(st)
#define luazombfunc(st) luaTable.Get<LuaFunction<LuaTable()>>(st)
#define newcomp(type, enum) world->getCompPool<type>(enum)->New()
#define addcomp(enum, comp) entity->components[enum] = comp

	entity->alliance = luaint("alliance");
	if (luabool("ChasingComp")) {
		//create chasing comp
//		CCLOG("creating chasing comp");
		entity->components[COMP_CA::CHASING_COMP] = world->commonComps[COMP_CA::CHASING_COMP];
	}
	if (luabool("SeperationComp")) {
//		CCLOG("creating seperation comp");
		entity->components[COMP_CA::SEPERATION_COMP] = world->commonComps[COMP_CA::SEPERATION_COMP];
	}
	if (luabool("FollowingComp")) {
//		CCLOG("creating followingComp");
		entity->components[COMP_CA::FOLLOWING_COMP] = world->commonComps[COMP_CA::FOLLOWING_COMP];
	}
	if (luabool("MeleeAttackComp")) {
//		CCLOG("creating meleeAttackComp");
		entity->components[COMP_CA::MELEE_ATTACK_COMP] = world->commonComps[COMP_CA::MELEE_ATTACK_COMP];
	}
	if (luabool("RangeAttackComp")) {
		//		CCLOG("creating rangeAttackComp");
		entity->components[COMP_CA::RANGE_ATTACK_COMP] = world->commonComps[COMP_CA::RANGE_ATTACK_COMP];
	}
	if (luabool("KeyboardComp")) {
//		CCLOG("creating keyboardComp");
		entity->components[COMP_CA::KEYBOARD_COMP] = world->commonComps[COMP_CA::KEYBOARD_COMP];
	}
	if (luabool("RecruitComp")) {
//		CCLOG("creating recruitComp");
		entity->components[COMP_CA::RECRUIT_COMP] = world->commonComps[COMP_CA::RECRUIT_COMP];
	}

	//pooled component
	if (luabool("ActionFlagComp")) {
//		CCLOG("creating actionflagComp");
		auto actionFlag = newcomp(ActionFlagComp, COMP_CA::ACTION_FLAG_COMP);
		actionFlag->init();
		actionFlag->interval = luafloat("attackSpeed");
		if (!luabool("belongToPlayer")) {
			actionFlag->interval = luafloat("WanderingCompInterval");
		}
		addcomp(COMP_CA::ACTION_FLAG_COMP, actionFlag);
		CCLOG("attack speed is %lf", actionFlag->interval);

	}
	if (luabool("AnimComp")) {
//		CCLOG("creating anim comp");
		auto anim = newcomp(AnimComp, COMP_CA::ANIM_COMP);
		anim->init();
		anim->name=luastring("AnimCompName");
		CCLOG("anim comp name is %s", anim->name.c_str());
		anim->newAnimState = A_WALK_FORTH;
		addcomp(COMP_CA::ANIM_COMP, anim);
	}
	//if (luabool("CombatComp")) {
//		CCLOG("creating combat comp");
		auto  combat = newcomp(CombatComp, COMP_CA::COMBAT_COMP);
		combat->init();
		combat->hp = luaint("hp");
		combat->damage = luaint("attack");
		//combat->attackSpeed = luafloat("attackSpeed");
		
		combat->alliance = entity->alliance;//TODO: set alliance in lua file
		CCLOG("damage is %d", combat->damage);
		addcomp(COMP_CA::COMBAT_COMP, combat);
	//}
	if (luabool("DomainComp")) {
//		CCLOG("creating domain comp");
		auto domain = newcomp(DomainComp, COMP_CA::DOMAIN_COMP);
		domain->init();
		domain->radius = (float)luaint("DomainCompRadius");
		CCLOG("Radius read is %d ", luaint("DomainCompRadius"));
		
		addcomp(COMP_CA::DOMAIN_COMP, domain);
	}
	if (luabool("HealComp")) {
//		CCLOG("creating heal comp");
		entity->components[COMP_CA::HEAL_COMP] = world->commonComps[COMP_CA::HEAL_COMP];
		//heal->healSpeed = luafloat("attackSpeed");
	}
	if (luabool("PointComp")) {
		//		CCLOG("creating point comp");

		auto pointComp = newcomp(PointComp, COMP_CA::POINT_COMP);
		addcomp(COMP_CA::POINT_COMP, pointComp);
	}
	if (luabool("HordeStatusComp")) {
		CCLOG("creating hordestatus comp");
		auto hordeStatus = newcomp(HordeStatusComp, COMP_CA::HORDE_STATUS_COMP);
		hordeStatus->init();
		hordeStatus->zombieCounts[ZOMBIE_CA::STINKIE] = luaint("StinkieNum");
		hordeStatus->zombieCounts[ZOMBIE_CA::CHUCKER] = luaint("ChuckerNum");
		hordeStatus->zombieCounts[ZOMBIE_CA::HOLY_BONE] = luaint("HolyBondNum");
		hordeStatus->zombieStat[ZOMBIE_STAT_CA::STINKIE_HP] = float(luaint("stinkieHP"));
		hordeStatus->zombieStat[ZOMBIE_STAT_CA::STINKIE_ATTACK] = float(luaint("stinkieAttack"));
		hordeStatus->zombieStat[ZOMBIE_STAT_CA::STINKIE_ATTACKSPEED] = luafloat("stinkieAttackSpeed");
		hordeStatus->zombieStat[ZOMBIE_STAT_CA::STINKIE_RANGE] = float(luaint("stinkieRange"));
		hordeStatus->zombieStat[ZOMBIE_STAT_CA::CHUCKER_HP] = luaint("chuckerHP");
		hordeStatus->zombieStat[ZOMBIE_STAT_CA::CHUCKER_ATTACK] = luaint("chuckerAttack");
		hordeStatus->zombieStat[ZOMBIE_STAT_CA::CHUCKER_ATTACKSPEED] = luafloat("chuckerAttackSpeed");
		hordeStatus->zombieStat[ZOMBIE_STAT_CA::CHUCKER_RANGE] = luaint("chuckerRange");
		hordeStatus->zombieStat[ZOMBIE_STAT_CA::HOLY_BONE_HP] = luaint("holyBoneHP");
		hordeStatus->zombieStat[ZOMBIE_STAT_CA::HOLY_BONE_HEAL] = luaint("holyBoneHeal");
		hordeStatus->zombieStat[ZOMBIE_STAT_CA::HOLY_BONE_ATTACK_SPEED] = luafloat("holyBoneAttackSpeed");
		hordeStatus->zombieStat[ZOMBIE_STAT_CA::HOLY_BONE_RANGE] = luaint("holyBoneRange");
//		CCLOG("holy bone STAT IS %lf %lf, %lf, %lf", hordeStatus->zombieStat[ZOMBIE_STAT_CA::HOLY_BONE_HP], hordeStatus->zombieStat[ZOMBIE_STAT_CA::HOLY_BONE_HEAL], hordeStatus->zombieStat[ZOMBIE_STAT_CA::HOLY_BONE_ATTACK_SPEED], hordeStatus->zombieStat[ZOMBIE_STAT_CA::HOLY_BONE_RANGE]);
//		CCLOG("stinkie STAT IS %lf %lf, %lf, %lf", hordeStatus->zombieStat[ZOMBIE_STAT_CA::STINKIE_HP], hordeStatus->zombieStat[ZOMBIE_STAT_CA::STINKIE_ATTACK], hordeStatus->zombieStat[ZOMBIE_STAT_CA::STINKIE_ATTACKSPEED], hordeStatus->zombieStat[ZOMBIE_STAT_CA::STINKIE_RANGE]);
//		CCLOG("chucker STAT IS %lf %lf, %lf, %lf", hordeStatus->zombieStat[ZOMBIE_STAT_CA::CHUCKER_HP], hordeStatus->zombieStat[ZOMBIE_STAT_CA::CHUCKER_ATTACK], hordeStatus->zombieStat[ZOMBIE_STAT_CA::CHUCKER_ATTACKSPEED], hordeStatus->zombieStat[ZOMBIE_STAT_CA::CHUCKER_RANGE]);

		int total = 0;
		for (int i = ZOMBIE_CA::ZOMBIE_START; i < ZOMBIE_CA::ZOMBIE_END; i++) {
			total += hordeStatus->zombieCounts[(ZOMBIE_CA)i];
		}
		hordeStatus->total = total;
		addcomp(COMP_CA::HORDE_STATUS_COMP, hordeStatus);
		
	}
	if (luabool("KineticComp")) {
//		CCLOG("creating kinetic comp");
		auto kinetic = newcomp(KineticComp, COMP_CA::KINETIC_COMP);
		kinetic->init();
		kinetic->maxSpeed = luafloat("KineticCompMaxSpeed");
		float x, y;
		if (luabool("belongToPlayer")) {
			KineticComp* playKin = (KineticComp*)(dynamic_cast<Zombie*>(entity))->player->components[COMP_CA::KINETIC_COMP];
			x = playKin->pos.x;
			y = playKin->pos.y;
		}
		else {
			x = luafloat("x");
			y = luafloat("y");
		}
//		CCLOG("the initial x and y is %f,%f", x, y);
		kinetic->pos.set(x, y);//TODO: zombie's position seems not working
		addcomp(COMP_CA::KINETIC_COMP, kinetic);
	}
	if (luabool("ZombieSensorComp")) {
//		CCLOG("creating zombie sensor comp");
		
		
	}
	if (luabool("WanderingComp")) {
//		CCLOG("creating wanderingComp");
		auto wanderingComp = newcomp(WanderingComp, COMP_CA::WANDERING_COMP);
		wanderingComp->init();
		addcomp(COMP_CA::WANDERING_COMP, wanderingComp);
	}
//	CCLOG("finish entity initialization");
}

Zombie* EntityFactory::createZombie(Player* player,LuaFunction<LuaTable()>& luaFunc) {
	CCLOG("creating zombie---------------------------");
	World* world = World::instance();
	Zombie* zombie = world->getZombiePool()->New();
	zombie->init();
	
	auto luaTable = luaFunc.Invoke();
	zombie->catagory =(ZOMBIE_CA) luaint("ZombieCatagory");
	zombie->player = player;
	initEntity(zombie,luaTable);
	world->zombieList.push_back(zombie);
	CCLOG("finish creating zombie---------------------");
	return zombie;
}
Zombie* EntityFactory::createStrayZombie(ZOMBIE_CA number) {
	World* world = World::instance();
	Zombie* zombie = world->getZombiePool()->New();
	zombie->init();
	auto lua = LuaDevice::instance();
	auto luaFunc = lua->global().Get<LuaFunction<LuaTable(bool)>>("createBasicStinkie");
	if (number == ZOMBIE_CA::HOLY_BONE) {
		luaFunc = lua->global().Get<LuaFunction<LuaTable(bool)>>("createBasicHolyBone");
	}
	else if (number == ZOMBIE_CA::CHUCKER) {
		luaFunc = lua->global().Get<LuaFunction<LuaTable(bool)>>("createBasicChucker");
	}
	auto luaTable = luaFunc.Invoke(false);
	initEntity(zombie, luaTable);
	zombie->catagory = (ZOMBIE_CA)luaint("ZombieCatagory");
	zombie->player = NULL;
	world->zombieList.push_back(zombie);
	//play spawn effect
	AttachmentFactory::createSpawnAtt(zombie);
	return zombie;
}

Player* EntityFactory::createPlayer(bool isHuman,bool isBoss, float gameTime) {
	World* world = World::instance();
	Player* player = world->getPlayerPool()->New();
	player->init();
	if (isHuman) {
		
		player->tint(Color3B(100, 255, 131));//light blue
	}
	else {
		player->tint(Color3B(253, 100, 255));
	}
	if (isBoss) {
		player->tint(Color3B(255, 100, 100));
	}
	//load lua file, 
	auto lua = LuaDevice::instance();
	LuaTable global = lua->global();
	CCLOG("the game time before is %d", global.Get<int>("time"));
	global.Set("time", (int)gameTime);
	CCLOG("the game time is %d", global.Get<int>("time"));
	auto luaFunc = lua->global().Get<LuaFunction<LuaTable(bool,bool)>>("createPlayer");
	auto luaTable =luaFunc.Invoke(isHuman,isBoss);
	initEntity(player,luaTable);

	//TODO:temporary:give player PowerUpComp so that he can pick up stuff, to be added to lua
	auto power = newcomp(PowerUpComp, COMP_CA::POWER_UP_COMP);
	power->init();
	player->components[COMP_CA::POWER_UP_COMP] = power;

	//create zombies for the player
	auto stinkieNum = (int)luafloat("StinkieNum");
	auto chuckerNum = (int)luafloat("ChuckerNum");
	auto holyNum = (int)luafloat("HolyBoneNum");
	CCLOG("for this player zombies num %d/%d/%d",stinkieNum, chuckerNum, holyNum);
	auto stinkieFunc = luazombfunc("StinkieFunc");
	auto chuckerFunc = luazombfunc("ChuckerFunc");
	auto holyFunc = luazombfunc("HolyBoneFunc");

	for (int i = 0; i < stinkieNum; i++) {
		createZombie(player, stinkieFunc)->tint(player->getColor());
	}
	//chuckerNum = 1;//create on chucker mannually
	//chuckerNum = 0;
	for (int i = 0; i < chuckerNum; i++) {
		auto zombie=createZombie(player, chuckerFunc);
		zombie->tint(player->getColor());
		/*
		//manually add a range attack comp, TODO: this is for testing only, should be handled by lua
		auto rangeComp = world->commonComps[COMP_CA::RANGE_ATTACK_COMP];
		zombie->components[COMP_CA::RANGE_ATTACK_COMP] = rangeComp;
		auto domainComp = (DomainComp*)zombie->components[COMP_CA::DOMAIN_COMP];
		if (!domainComp) {
			domainComp = newcomp(DomainComp, COMP_CA::DOMAIN_COMP);
			zombie->components[COMP_CA::DOMAIN_COMP] = domainComp;
		}
		domainComp->radius = 700.0f;//set a super large radius
		*/
	}
	for (int i = 0; i < holyNum; i++) {
		auto zombie=createZombie(player, holyFunc);
		zombie->tint(player->getColor());
		auto domainComp = (DomainComp*)zombie->components[COMP_CA::DOMAIN_COMP];
		if (!domainComp) {
			domainComp = newcomp(DomainComp, COMP_CA::DOMAIN_COMP);
			zombie->components[COMP_CA::DOMAIN_COMP] = domainComp;
		}
		domainComp->radius = 700.0f;//set a super large radius
	}
	//add player to the world
	world->playerList.push_back(player);
	AttachmentFactory::createSpawnAtt(player);
	//player->tint(Color3B::MAGENTA);//test, tint all the player to magenta, TODO::remove it. read from lua.
	return player;
}
Item* EntityFactory::createBullet(Entity* user, Vec2 destination) {
	World* world = World::instance();
	Item* entity = world->getItemPool()->New();
	entity->init();
	//TODO load data from lua file
	//for now. manually create the components. 
//1. kinetic comp
	auto kinComp = newcomp(KineticComp, COMP_CA::KINETIC_COMP);
	kinComp->init();
	auto userKinComp =(KineticComp*)user->components[KINETIC_COMP];
	if (userKinComp) {
		kinComp->pos.set(userKinComp->pos);//set the original position as the zombie's postion
		addcomp(COMP_CA::KINETIC_COMP, kinComp);
		CCLOG("item created kinetic comp");
	}
	
//2. domain comp
	auto domainComp = newcomp(DomainComp, COMP_CA::DOMAIN_COMP);
	domainComp->init();
	domainComp->radius = 100.0f;//splash damage within 100 px radius
	addcomp(COMP_CA::DOMAIN_COMP, domainComp);
//3. alliance
	entity->alliance = user->alliance;
	//TODO: change all the alliance calculation to entity instead of combat component
//4. TrajectComp: new comp, mark that this is a bullet. also record damage. Note that bullet doesn't have combat comp, so it wont be attacked. 
	auto trajectComp = newcomp(TrajectComp, COMP_CA::TRAJECT_COMP);
	trajectComp->init();
	trajectComp->target.set(destination);
	trajectComp->origin.set(kinComp->pos);
	addcomp(COMP_CA::TRAJECT_COMP, trajectComp);
//5. AnimComp
	auto animComp = newcomp(AnimComp, COMP_CA::ANIM_COMP);
	animComp->init();
	animComp->name = "spit";
	//animComp->animState = A_FLY;
	animComp->newAnimState = A_FLY;
	animComp->directional = 0;
	animComp->defaultAction = A_FLY;
	addcomp(COMP_CA::ANIM_COMP, animComp);


	world->itemList.push_back(entity);
	return entity;
}

Item* EntityFactory::createPickUp(ITEM_CA type, Vec2 location) {
	World* world = World::instance();
	Item* entity = world->getItemPool()->New();
	entity->init();
	//TODO load data from lua file
	//for now. manually create the components. 
	//1. kinetic comp
	auto kinComp = newcomp(KineticComp, COMP_CA::KINETIC_COMP);
	kinComp->init();
	kinComp->pos.set(location);
	addcomp(COMP_CA::KINETIC_COMP, kinComp);
	CCLOG("item created kinetic comp");
	
	//2. domain comp, use to check if character touches it
	auto domainComp = newcomp(DomainComp, COMP_CA::DOMAIN_COMP);
	domainComp->init();
	domainComp->radius = 50.0f;//character within 50 can pick up
	addcomp(COMP_CA::DOMAIN_COMP, domainComp);
	//3. alliance, well neutral
	entity->alliance = 0;
	
	//4. AnimComp
	auto animComp = newcomp(AnimComp, COMP_CA::ANIM_COMP);
	animComp->init();
	animComp->name = EFFECT_STR;
	//animComp->animState = A_FLY;
	switch (type) {
	case ITEM_CA::ITEM_ATTACK:
		animComp->newAnimState = I_PICKUP_ATTACK;
		animComp->defaultAction = I_PICKUP_ATTACK;
		break;
	case ITEM_CA::ITEM_SPEED:
		animComp->newAnimState = I_PICKUP_SPEED;
		animComp->defaultAction = I_PICKUP_SPEED;
		break;
	case ITEM_CA::ITEM_INVIN:
		animComp->newAnimState = I_PICKUP_SHIELD;
		animComp->defaultAction = I_PICKUP_SHIELD;
		break;
	case ITEM_CA::ITEM_HEALTH:
		animComp->newAnimState = I_PICKUP_HEALTH;
		animComp->defaultAction = I_PICKUP_HEALTH;
		break;
	}
	animComp->directional = 0;
	addcomp(COMP_CA::ANIM_COMP, animComp);
	//5. powerUpComp, the most important one
	auto powerComp = newcomp(PowerUpComp, COMP_CA::POWER_UP_COMP);
	powerComp->init();
	powerComp->type = type;
	if (type == ITEM_CA::ITEM_HEALTH || type == ITEM_CA::ITEM_NONE) {
		powerComp->instant = true;
	}
	addcomp(COMP_CA::POWER_UP_COMP, powerComp);

	world->itemList.push_back(entity);
	return entity;
}
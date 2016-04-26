#include "KineticComp.h"
#include "world/World.h"
#include "util/GameKey.h"
#include "component/pooled/KineticComp.h"
KineticComp::KineticComp() {
    
}
void KineticComp::init() {
	this->vel.set(0.0f, 0.0f);
	this->pos.set(0.0f, 0.0f);
	this->acc.set(0.0f, 0.0f);
}
void KineticComp::step(Entity* entity, float delta) {
	Vec2 increment(vel);
	increment.scale(delta);
	pos.add(increment);
	//CCLOG("Swiss position %f", pos.length());
	entity->sprite->setPosition(pos);
	//CCLOG("Swiss sprite position %f %f", dynamic_cast<Player*>(entity)->sprite->getPositionX(), dynamic_cast<Player*>(entity)->sprite->getPositionY());
	
}
/*
void KineticComp::stepZ(Entity* entity) {
	pos.add(vel);
	dynamic_cast<Zombie*>(entity)->sprite->setPosition(pos);

}*/
//will delete later, for now use to render non moving zombies
void KineticComp::setSpritePos(Entity* entity) {
	dynamic_cast<Zombie*>(entity)->sprite->setPosition(pos);
}

void KineticComp::setPos( float x, float y) {
	pos.set(Vec2(x, y));
}
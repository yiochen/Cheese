#include "BoxHelper.h"
#include "cocos2d.h"

using namespace cocos2d;

BoxHelper::BoxHelper() {
	W2S = 30.0f;
	S2W = 1.0f/30.0f;
}

void BoxHelper::initBox2d() {
	b2Vec2 gravity;
	gravity.Set(0.0f, -9.8f);

	bool doSleep = true;

	world = new b2World(gravity);
	world->SetAllowSleeping(doSleep);


	float halfWidth = this->width / 2;
	float halfHeight = this->height / 2;
	float bhalfThick = 1.0f;
	float bhalfLong = this->width/2;
	//create four border;
	//up
	//createStaticRect(halfWidth, this->height+bhalfThick, bhalfThick * 2, this->width,NULL);
	//down
	createStaticRect(halfWidth, - bhalfThick,  this->width, bhalfThick * 2, NULL);
	//left
	createStaticRect(-bhalfThick, halfHeight,  bhalfThick * 2, this->height ,NULL);
	//right
	createStaticRect(this->width+ bhalfThick, halfHeight, bhalfThick * 2, this->height, NULL);
	

}

b2Body* BoxHelper::createStaticRect(float x, float y, float width, float height, Sprite *sp) {
	//create world boundary
	//create body
	b2Body *body;

	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(x, y);
	bodyDef.userData = sp;
	body = world->CreateBody(&bodyDef);
	//create fixture
	b2PolygonShape rectShape;
	rectShape.SetAsBox(width/2, height/2);
	b2FixtureDef shapeDef;
	shapeDef.shape = &rectShape;
	shapeDef.friction = 0.4f;

	b2Fixture * fixture = body->CreateFixture(&shapeDef);
	return body;
}
b2Body* BoxHelper::createDynamicRect(float x, float y, float width, float height, Sprite *sp) {
	b2Body *body;
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(x, y);
	bodyDef.angle = 0;
	bodyDef.userData = sp;
	body = world->CreateBody(&bodyDef);
	//create fixture
	b2PolygonShape rectShape;
	rectShape.SetAsBox(width/2, height/2);
	b2FixtureDef shapeDef;
	shapeDef.shape = &rectShape;
	shapeDef.friction = 0.4f;
	shapeDef.density = 1;

	b2Fixture * fixture = body->CreateFixture(&shapeDef);
	
	return body;
}
void BoxHelper::update(float delta) {
	this->world->Step(delta, this->velIterations, this->posIterations);
}

BoxHelper::~BoxHelper() {
	//remove world
	delete this->world;
}
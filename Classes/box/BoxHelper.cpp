#include "BoxHelper.h"
#include "cocos2d.h"

using namespace cocos2d;

BoxHelper::BoxHelper() {
    
}

void BoxHelper::initBox2d() {
	b2Vec2 gravity;
	gravity.Set(0.0f, -10.0f);

	bool doSleep = true;

	world = new b2World(gravity);
	world->SetAllowSleeping(doSleep);

	float x, y;
	float width, height;
	Sprite* sp;
	
	

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
	rectShape.SetAsBox(width, height);
	b2FixtureDef shapeDef;
	shapeDef.shape = &rectShape;
	shapeDef.friction = 0.4f;

	b2Fixture * fixture = body->CreateFixture(&shapeDef);
	return body;
}
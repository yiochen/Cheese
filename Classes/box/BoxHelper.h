#pragma once
#include "Box2D\Box2D.h"
#include "cocos2d.h"

USING_NS_CC;
class BoxHelper {
private:
	b2World* world;
public:
    BoxHelper();
	void initBox2d();
	b2Body * createStaticRect(float x, float y, float width, float height, Sprite *sp);
};

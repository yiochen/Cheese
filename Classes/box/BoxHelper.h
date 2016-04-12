#pragma once
#include "Box2D\Box2D.h"
#include "cocos2d.h"

USING_NS_CC;
//this helper class creates a world, centering at the bottom left corner of the screen.
class BoxHelper {
private:
	float width;
	float height;
	float sceneWidth;
	float sceneHeight;
	b2World* world;
	int velIterations = 8;
	int posIterations = 4;

public:
	float W2S;
	float S2W;
    BoxHelper();
	~BoxHelper();
	void initBox2d();
	void setSize(float width, float height) {
		this->width = width*S2W; 
		this->height = height*S2W;
		this->sceneWidth = width;
		this->sceneHeight = height;
	}
	b2Body * createStaticRect(float x, float y, float width, float height, Sprite *sp);
	b2Body * createDynamicRect(float x, float y, float width, float height, Sprite *sp);
	float getSceneX(b2Body* body) {
		return body->GetPosition().x*W2S;
	}
	float getSceneY(b2Body* body) {
		return body->GetPosition().y*W2S;
	}
	void update(float delta);
	//convert coordinates
	//scene x to world

};

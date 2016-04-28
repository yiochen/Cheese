#pragma once
#include "cocos2d.h"

class LoadScene:public cocos2d::Layer {
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	CREATE_FUNC(LoadScene);
	void preload(float dt);
	void transit(float dt);
};

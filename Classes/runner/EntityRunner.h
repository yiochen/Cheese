#pragma once

/*
*	EntityRunner is an abstract class
*/
class EntityRunner {
public:
    EntityRunner();
	virtual void update(float delat) = 0;
};

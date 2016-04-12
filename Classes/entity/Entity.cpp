#include "Entity.h"

Entity::Entity() {
    
}

Entity::~Entity() {
	//TODO
	//free all resource
	//set all pointers to NULL
	//remove all the components from the component list
	sprite = NULL;
}
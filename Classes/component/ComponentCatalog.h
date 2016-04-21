#pragma once

enum COMP_CA {
	//basic component
	//to create, use "new", to remove, use "delete"
	KEYBOARD_COMP,
	CHASING_COMP,


	//pooled component
	//to create, use "objectPool.New()" and then initialize the component, to remove use "pool.Delete(test)", this will call the destructor, but not deleting the object
	KINETIC_COMP,
	ANIM_COMP,
	DOMAIN_COMP
};
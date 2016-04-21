#pragma once

/*
There are two kinds of components, normal one and pooled one.
Normal components don't contain any customized data. They should be created only once and shared by all entities that need.
Some of the normal components include 
1. components that contains shared data, 
2. components that is merely a marker.
*/
class Comp {
public:
    Comp();
	virtual ~Comp() {}
};

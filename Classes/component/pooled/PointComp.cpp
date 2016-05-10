#include "PointComp.h"

PointComp::PointComp() {
	point = 0;

}

void PointComp::init() {
	point = 0;
}

void PointComp::add(Entity* e, int add) {
	PointComp* pointComp = (PointComp*)e->components[COMP_CA::POINT_COMP];
	if (pointComp) {
		pointComp->point += add;
	}

}
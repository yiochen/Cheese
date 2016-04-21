#include "DomainComp.h"

DomainComp::DomainComp() {
	radius = 0;
}
bool DomainComp::contains(Vec2 center, Vec2 target) {
	return (center.distance(target) <= radius);
}
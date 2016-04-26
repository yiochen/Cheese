#include "util/AnimNameHelper.h"
#include "cocos2d.h"
USING_NS_CC;
std::string anim_name::directionalString(std::string prefix, Vec2 direction) {
	 stringstream ss;
	 ss << prefix << '_';
	 float angle = direction.getAngle();
	 if (angle < PI / 4 && angle > -PI / 4) {
		 //moving right 
		 ss << A_RIGHT;

	 }
	 else if (angle >= PI / 4 && angle < 3 * PI / 4) {
		 ss << A_BACK;

		 //moving up
	 }
	 else if (angle >= 3 * PI / 4 || angle < -3 * PI / 4) {
		 ss << A_LEFT;

		 //moving left
	 }
	 else {
		 ss << A_FORTH;

		 //moving forward
	 }
	 return ss.str();
	}
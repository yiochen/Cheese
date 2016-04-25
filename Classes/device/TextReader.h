#pragma once

#include <fstream>
#include <sstream>
#include <string>

#include "cocos2d.h"

USING_NS_CC;
using namespace std;
namespace device {
	string read(string path, bool& success);
}

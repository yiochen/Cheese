#include "TextReader.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "cocos2d.h"
USING_NS_CC;
string device::read(string path, bool& success) {
	string script;
	string absPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(path);
	CCLOG("the abs path is %s", absPath);
	ifstream file(absPath);
	CCLOG("created the file object");
	bool failed=file.fail();
	CCLOG("pass here");
	if (!failed) {
		CCLOG("pass here too");
		//CCLOG("successfully read %s", absPath);
		//successfully opened the file
		script=string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
		CCLOG("PAss here htoo");
		success = true;
		CCLOG("pass here too");
	}
	else {
		CCLOG("open file failed");
		success = false;
	}
	CCLOG("returning the script");
	return script;
}
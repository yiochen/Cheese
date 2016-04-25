#pragma once

/*This is the configuration file for any important game data. 
It contains for example the width and height of the world
The values of the field could be initialized through lua. */

class Config {
private:
	static Config* s_instance;
	Config();
public:
	static Config* instance() {
		if (!s_instance) {
			s_instance = new Config();
		}
		return s_instance;
	}
	void init();
	float WORLD_HEIGHT;
	float WORLD_WIDTH;
};

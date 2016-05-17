#pragma once

/*This is the configuration file for any important game data. 
It contains for example the width and height of the world
The values of the field could be initialized through lua. */

class Config {
private:
	static Config* s_instance;
	bool initialized;
	Config();
public:
	static Config* instance() {
		if (!s_instance) {
			s_instance = new Config();
			if (!s_instance->initialized) {
				s_instance->init();
			}
		}
		return s_instance;
	}
	void init();
	float WORLD_HEIGHT;
	float WORLD_WIDTH;
	int screen_height;
	int screen_width;
	bool fullscreen;
	//debug_mode is set by lua file (config.lua). When debug_mode is true, some functionality is turned off, for example, zombie spawning.
	bool debug_mode;
};

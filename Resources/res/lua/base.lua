--base
--this file requires all the lua files.
--this is used as a entry point. run process.py to generate a concat version of lua script containing all the scripts.
require "config"
require "sprite_config"
require "Object"
require "Entity"
require "Game"
require "Vector"
require "Zombie"
require "Player"
require "Item"

print(newPlayer(true,PLAYER_CA.SWISS))
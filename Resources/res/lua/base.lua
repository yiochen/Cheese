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

player=Player(true,PLAYER_CA.SWISS)
zombie=Zombie(player, ZOMBIE_CA.CHUCKER)

print(player)
print(zombie)
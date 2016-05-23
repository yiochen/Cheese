--base
--This is the base lua script for testing
--it will load all the lua scripts and run test 
--in C++, this script will not be called. instead, all the scripts will be concate and read all at once. 
require "Entity"
require "Vector"
require "Zombie"
require "Player"

player=Player(true,PLAYER_CA.SWISS)
zombie=Zombie(player, ZOMBIE_CA.CHUCKER)

print(player)
print(zombie)
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
require "level"

game=Game()
game:setMode(GAME_MODE.ENDLESS)
function getWave(waveIndex)
  return game:getWave(waveIndex)
end
print(getWave(0))
print(getWave(0).playerList[0].zombieList.count)
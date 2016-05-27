--mode: endless

require "Game"
require "Wave"

function Game:getWave(waveIndex)
  local wave=Wave()
  local players=Wave.playerList
  local zombies=Wave.zombieList
  --endless mode
  
  if (self.mode==GAME_MODE.ENDLESS)
  then
    
  end
  
  if (self.mode==GAMG_MODE.LEVEL)
  then
    if (waveIndex==0)
    then
      wave.category=WAVE_CA.PREP
      wave.maxTime=10
      return wave
    end
    
    
  end
  
  if (self.mode==GAME_MODE.PK)
  then
  end
  
  if (self.mode==GAME_MODE.COLLAB)
  then
  end
  
  
end



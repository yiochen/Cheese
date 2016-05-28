--mode: endless

require "Game"
require "Wave"

--level design status
--endless level wave 0- 3
--level-mode level 0, wave 0-1

function perX(percent)
  return Game.worldWidth*percent
end

function perY(percent)
  return Game.worldHeight*percent
end

function Game:getWave(waveIndex)
  local wave=Wave()
  local players=Wave.playerList
  local zombies=Wave.zombieList
---------------------------------------------endless mode------------------------------
  
  if (self.mode==GAME_MODE.ENDLESS)
  then
    if (waveIndex==0)
    then
      wave.category=WAVE_CA.PREP
      wave.maxTime=60 --second
      local player=newHuman()
      player:setPos(perX(0.5), perY(0.5))
      wave:push(player)
      return wave
    end
    --wave 1-3 only stinkie, every player 4 zombies
    if (waveIndex>0 and waveIndex<=3)
    then
      wave.category=WAVE_CA.NORMAL
      wave.maxTime=60 --second
      for i=0,waveIndex,1:
      do
        local enemy=newEnemy()
        enemy:setPos(perX(1/(waveIndex+1)*(i+1)), perY(0.5))
        --create zombie for each player
        for j=0,3,1:
        do
          wave:push(Zombie(enemy, ZOMBIE_CA.STINKIE)
        end
        wave:push(player)
      end
      
      
      return wave
    end
    
  end
 ---------------------------------------------level mode ------------------------------ 
  if (self.mode==GAMG_MODE.LEVEL)
  then
    if (waveIndex==0)
    then
      wave.category=WAVE_CA.PREP
      wave.maxTime=10 --second
      local player=newHuman()
      player:setPos(perX(0.5), perY(0.5))
      wave:push(player)
      return wave
    end
    if （self.level==0 and waveIndex==1)
    then
      wave.category=WAVE_CA.NORMAL
      wave.maxTime=60
      local enemy=newEnemy()
      enemy:setPos(perX(0.25), perY(0.5))
      wave:push(enemy)
      enemy=newEnemy()
      enemy:setPos(perX(0.75), perY(0.5))
      wave:push(enemy)
      return wave
    end
  end --mode level
  
  if (self.mode==GAME_MODE.PK)
  then
  end
  
  if (self.mode==GAME_MODE.COLLAB)
  then
  end
  
  
end



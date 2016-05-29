--mode: endless

require "Game"
require "Wave"

--level design status
--endless level wave 0- 3
--level-mode level 0, wave 0-1

---------------------------------------helper functions-------------------------------
function perX(percent)
  return Game.worldWidth*percent
end

function perY(percent)
  return Game.worldHeight*percent
end

function alignHorX(index, total)
  return perX(1/(total+1)*(index+1))
end

function alignHorY(index, total)
  return perY(0.5)
end

function alignVerY(index, total)
  return perY(1/(total+1)*(index+1))
end

function alginVerX(index, total)
  return perX(0.5)
end

function alignHor2X(index, total)
  local up=math.floor(total/2)
  local down=total-up
  if (index<up)
  then
    return perX(1/(up+1)*(index+1))
  end
  
  if (index>=up)
  then
    return perX(1/(down+1)*(index-up+1))
  end
end

function alignHor2Y(index, total)
  local up=math.floor(total/2)
  local down=total-up
  if (index<up)
  then
    return perY(1/3)
  end
  
  if (index>=up)
  then
    return perY(2/3)
  end
end

-------------------------------------end of helper functions----------------------------

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
      for i=0,waveIndex,1
      do
        local enemy=newEnemy()
        enemy:setPos(perX(1/(waveIndex+1)*(i+1)), perY(0.5))
        --create zombie for each player
        for j=0,3,1
        do
          wave:push(Zombie(enemy, ZOMBIE_CA.STINKIE)) --only stinkies
        end
        wave:push(enemy)
      end
      return wave
    end
    
    --wave 4-5 add chuckers, every player 4 zombies
    if (waveIndex>=4 and waveIndex<=5)
    then
      wave.category=WAVE_CA.NORMAL
      wave.maxTime=120
      for i=0, waveIndex-1, 1
      do
        local enemy=newEnemy()
        enemy: setPos(perX(1/(waveIndex+1)*(i+1)), perY(0.5))
        for j=0,1,1
        do 
          wave:push(Zombie(enemy, ZOMBIE_CA.CHUCKER))
          wave:push(Zombie(enemy, ZOMBIE_CA.STINKIE))
        end
        wave:push(enemy)
        return wave
      end
    end
  
    --wave 6-7 add holybone, every player 5 zombies, 2 stinkie, two chuckers, one holy bone
    if (waveIndex>=6 and waveIndex<=7)
    then
      wave.category=WAVE_CA.NORMAL
      wave.maxTime=150
      for i=0, waveIndex-2,1
      do
        local enemy=newEnemy()
        enemy:setPost(alignHor2X(i,waveIndex-1),alginHor2Y(i, waveIndex-1))
        for j=0,1,1
        do
          wave:push(Zombie(enemy, ZOMBIE_CA.STINKIE))
          wave:push(Zombie(enemy, ZOMBIE_CA.CHUCKER))
        end
        wave:push(Zombie(enemy, ZOMBIE_CA.HOLY_BONE))
        wave:push(enemy)
        return wave
      end
    end
  
    if (waveIndex>7)
    then
      wave.category=WAVE_CA.NONE --haven't construct yet
      return wave
    end
  end--endless mode
  
    
 ---------------------------------------------level mode ------------------------------ 
  if (self.mode==GAME_MODE.LEVEL)
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
    if (self.level==0 and waveIndex==1)
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

--game=Game()
--game:setMode(GAME_MODE.ENDLESS)
--wave=game:getWave(1)
--print(wave)

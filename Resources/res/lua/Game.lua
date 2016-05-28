--game
--game environement related 
require "Object"
require "config"


GAME_MODE={
  LEVEL=0,
  ENDLESS=1,
  COLLAB=2,
  PK=3
}

Game=createType("Game",Object)

Game:addMembers({
    difficulty=1,
    waveAmount=1, --  -1 means endless
    currentWave=-1,
    time=0,
    mode=GAME_MODE.LEVEL,
    level=0,
    worldHeight=config.WORLD_HEIGHT,
    worldWidth=config.WORLD_WIDTH,
  })

function Game:setMode(mode)
  asset(mode>=0 and mode<=3)
  self.mode=mode
  if (self.mode==GAME_MODE.LEVEL)
  then
    self.level=0
  end
end

function Game:setLevel(level)
  self:setMode(GAME_MODE.LEVEL)
  self.level=level
end

function Game:getNextWave()
  self.currentWave=self.currentWave+1
  return self:getWave(self.currentWave)
end

  


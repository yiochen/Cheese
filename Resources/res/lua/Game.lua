--game
--game environement related 
require "Object"

GAME_MODE={
  LEVEL=0,
  ENDLESS=1,
  COLLAB=2,
  PK=3
}

Game=createType("Game",Object)

Game:addMembers({
    difficulty=1,
    time=0,
    mode=GAME_MODE.LEVEL,
    level=0,
    worldWidth=700,
    worldHeight=700,
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




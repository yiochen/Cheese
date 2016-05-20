--game
--game environement related 
require "Object"

Game=createType("Game",Object)

Game:addMembers({
    difficulty=1,
    time=0,
    worldWidth=700,
    worldHeight=700,
  })

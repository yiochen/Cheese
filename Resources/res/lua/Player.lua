--Player

require "Object"
require "Entity"

Player=createType("Player", Entity)

Player:addMembers({
    isHuman=false,
    category=0
  })

function Player:new(isHuman, category)
  
end

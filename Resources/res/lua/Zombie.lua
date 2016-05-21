--Zombie

require "Object"
require "Entity"


Zombie=createType("Zombie",Entity)

Zombie:addMembers({
    player,
    })
function Zombie:new(player)
  if (player.__typename=="Player")
  then
    self.alliance=player.alliance
    self.color=player.color
  end
end

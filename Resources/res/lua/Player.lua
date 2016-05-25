--Player
--Player(isHuman, category)
require "Object"
require "Entity"
require "Item"

Player=createType("Player", Entity)

PLAYER_CA={
  SWISS=1,
  BILL=2,
  }
Player:addMembers({
    isHuman=false,
    category=0
  })

function Player:new(isHuman, category)
  self.isHuman=isHuman
  self.category=category
  
  if (isHuman)
  then
    self.alliance=1
    self:addComp("KeyboardComp")
  else
    self.alliance=2
    self:addWandering()
  end
  
  self:addComp("RecruitComp")
  self:addKinetic(Vector(300,300), Vector(0,0), 100)
  self:addDomain(50)
  self:addHordeStatus()
  self:addCombat(0,0)
  self:addPowerUp(ITEM_CA.ITEM_NONE,true)
  if (category==PLAYER_CA.SWISS)
  then
    self:addAnim("swiss","WALK_FORTH", "WALK")
  else if (category==PLAYER_CA.BILL)
    then
      self:addAnim("enemy","WALK_FORTH", "WALK")
    end
  end
  
  self:addPoint()
end

function newPlayer(isHuman, category)
  return Player(isHuman, category)
end

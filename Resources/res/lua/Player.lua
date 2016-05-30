--Player
--Player(isHuman, category)
require "Object"
require "Entity"
require "Item"
require "Zombie"

Player=createType("Player", Entity)

PLAYER_CA={
  SWISS=1,
  BILL=2,
  }
Player:addMembers({
    isHuman=false,
    category=0,
    zombieLevels={},
    zombieList={count=0},
  })

function Player:new(isHuman, category)
  self.isHuman=isHuman
  self.category=category
  self.zombieLevels={}
  self.zombieList={count=0}
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
function Player:getZombieAmount(category)
  return self.zombieAmounts[category] or 0
end
function Player:getZombie(category)
  return Zombie(self,category)
end

function Player:push(zombie)
  self.zombieList[self.zombieList.count]=zombie
  self.zombieList.count=self.zombieList.count+1
  return self
end

getmetatable(Player).__tostring=function(p)
  return "Player:{ aliance: "..p.alliance..", type: "..p.category..", pos:"..tostring(p.kinetic_pos).."}"
end


function newPlayer(isHuman, category)
  return Player(isHuman, category)
end

--various player type
function newHuman()
  local player=Player(true, PLAYER_CA.SWISS)
  player.zombieLevels[ZOMBIE_CA.STINKIE]=0
  player.zombieLevels[ZOMBIE_CA.CHUCKER]=0
  player.zombieLevels[ZOMBIE_CA.HOLY_BONE]=0
  return player
end

function newEnemy()
  --TODO: this should base on the global game stage and difficulty
  local player=Player(false,PLAYER_CA.BILL)
  player.zombieLevels[ZOMBIE_CA.STINKIE]=0
  player.zombieLevels[ZOMBIE_CA.CHUCKER]=0
  player.zombieLevels[ZOMBIE_CA.HOLY_BONE]=0
  return player
end



--human=newEnemy()
--print(human:getZombieAmount(ZOMBIE_CA.STINKIE))
--print(human:getZombie(ZOMBIE_CA.STINKIE))
--Zombie
--Zombie(player, category)
require "Object"
require "Entity"
require "Vector"

ZOMBIE_CA={
  STINKIE=1,
	CHUCKER=2,
	HOLY_BONE=3
}

--get zombie's stat by category and level
function zStatByLevel(category, level)
  assert(level>=0 and level<=5)--maximum level=5
  local stat={
    hp=0,
    attack=0,
    attackSpeed=100, --in seconds
  }
  if (category==ZOMBIE_CA.STINKIE)
  then
    stat.hp=10+level*2
    stat.attack=5+level*1
    stat.attackSpeed=1.5-level*0.1
  else if (category==ZOMBIE_CA.CHUCKER)
    then
      stat.hp=15+level*2
      stat.attack=4+level*2
      stat.attackSpeed=5.0-0.2*level
    else if (category==ZOMBIE_CA.HOLY_BONE)
      then
        stat.hp=20+level*3
        stat.attack=2+level*1
        stat.attackSpeed=5.0-0.2*level
      end
    end
  end
  return stat
end

Zombie=createType("Zombie",Entity)

Zombie:addMembers({
    player=nil,
    category=0
  })

function Zombie:new(player, category)
  self.category=category
  self.player=player
  if (player and player.__typename=="Player")
  then
    self.alliance=player.alliance
    self.color=player.color
    assert(type(player.domain_radius)=="number")
    local r=math.random(player.domain_radius)
    local angle=math.random(360)
    local v=Vector(0,r):rotate(angle)
    
    self:addKinetic(player.kinetic_pos+v,Vector(0,0),100)
  else
    self:addKinetic(Vector(300,300),Vector(0,0),100)
  end
  self:addComp(
    "ChasingComp",
    "SeperationComp",
    "FollowingComp"
  )
  if (category==ZOMBIE_CA.STINKIE)
  then
    self:createStinkie()
  else if (category==ZOMBIE_CA.CHUCKER)
    then
      self:createChucker()
    else if (category==ZOMBIE_CA.HOLY_BONE)
      then
        self:createHolyBone()
      end
    end
  end
  
  if (nil==player)
  then
    self:addWandering()
  end
end

getmetatable(Zombie).__tostring=function(p)
  return "Zombie:{ aliance: "..p.alliance..", type: "..p.category..", pos:"..tostring(p.kinetic_pos)..", player: "..tostring(p.player).."}"
end

function Zombie:createStinkie()
  self:addDomain(100)
  self:addCombat(0,0)--combat stat will be modified when the zombie is recruited
  self:addAnim("basic_zombie", "WALK_FORTH", "WALK")
  self:addComp("MeleeAttackComp")
  
end

function Zombie:createChucker()
  self:addDomain(500)
  self:addCombat(0,0)
  self:addAnim("chucker", "WALK_FORTH", "WALK")
  self:addComp("RangeAttackComp")
end

function Zombie:createHolyBone()
  self:addDomain(200)
  self:addCombat(0,0)
  self:addAnim("healer", "WALK_FORTH", "WALK")
  self:addComp("HealComp")
end



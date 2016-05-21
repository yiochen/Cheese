--entity

require "Object"
require "Vector"

Entity=createType("Entity",Object)

Entity:addMembers({
    alliance=0,
    color=0xffffff,
    --add all the components
    --basic
    ChasingComp=false,
    EscapeComp=false,
    FollowingComp=false,
    HealComp=false,
    KeyboardComp=false,
    MeleeAttackComp=false,
    RangeAttackComp=false,
    RecruitComp=false,
    SeperationComp=false,
    
    --pooled
    ActionFlagComp=false,
    AnimComp=false,
    CombatComp=false,
    DomainComp=false,
    HordeStatusComp=false,
    KineticComp=false,
    PointComp=false,
    PowerUpComp=false,
    TrajectComp=false,
    WonderingComp=false,
  })

function Entity:addComp(...)
  for key, value in pairs({...})
  do
    assert(type(self[value])=="boolean")
    self[value]=true
  end
end

function Entity:addActionFlag(interval)
  assert(type(interval)=="number")
  self:addComp("ActionFlagComp")
  self.actionFlag_interval=interval
end

function Entity:addAnim(name, newAnimState,defaultAction)
  assert(type(defaultAction)=="string")
  self:addComp("AnimComp")
  self.anim_name=name;
  self.anim_newAnimState=newAnimState
  self.anim_defaultAction=defaultAction
end

function Entity:addCombat(hp,damage)
  assert(type(damage)=="number")
  self:addComp("CombatComp")
  self.combat_hp=hp
  self.combat_damage=damage
end

function Entity:addDomain(radius)
  assert(type(radius)=="number")
  self:addComp("DomainComp")
  self.domain_radius=radius
end

function Entity:addHordeStatus()
  self:addComp("HordeStatusComp")
end

function Entity:addKinetic(pos, vel, maxSpeed)
  assert(pos.__typename=="Vector" and vel.__typename=="Vector" and type(maxSpeed)=="number")
  self:addComp("KineticComp")
  self.kinetic_posX=pos.x
  self.kinetic_posY=pos.y
  self.kinetic_velX=vel.x
  self.kinetic_velY=vel.y
  self.kinetic_maxSpeed=maxSpeed
end

function Entity:addPointComp()
  self:addComp("PointComp")
end

function Entity:addPowerUpComp(powerUpType, instant)
  assert(type(intant)=="boolean")
  self:addComp("PowerUpComp")
  self.powerUp_type=powerUpType
  self.powerUp_instant=instant
end

function Entity:addTrajectComp(speed)
  assert(type(speed)=="number")
  self:addComp("TrajectComp")
  self.traject_speed=speed
end

function Entity:addWanderingComp()
  self:addComp("WanderingComp")
end
  
  

--testing
entity=Entity()

entity:addComp("ChasingComp","SeperationComp")
print(entity)


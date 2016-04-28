--dynamic zombie creating based on how much killed?
--time is in seconds elapsed?
--difficulty 1/2/3   easy/med/hard
gameTable = {difficulty = 1, time = 45}
--time is to be updated whenever you create a scaling zombie, in seconds
gameTable.worldWidth = 700
gameTable.worldHeight = 700
gameTable.maxSpeed = 100.0
gameTable.maxPlayerSpeed = 130.0
--stats i need to know to create a zombie according to players current upgrade, to be updated before zombie creation
gameTable.chuckerHP = 7
gameTable.chuckerAttack = 1
gameTable.chuckerAttackSpeed = 1.5
gameTable.chuckerRange = 100

gameTable.stinkieHP = 10

gameTable.stinkieAttack = 30

gameTable.stinkieAttackSpeed = 2.0
gameTable.stinkieRange = 50

gameTable.holyBoneHP = 5
gameTable.holyBoneAttack = 0
gameTable.holyBoneAttackSpeed = 3.0
gameTable.holyBoneRange = 100
gameTable.holyBoneHeal = 1



--stats for basic zombie attributes
gameTable.basicChuckerHP = 7
gameTable.basicChuckerAttack = 1
gameTable.basicChuckerAttackSpeed = 1.5
gameTable.basicChuckerRange = 100

gameTable.basicStinkieHP = 10
gameTable.basicStinkieAttack = 2
gameTable.basicStinkieAttackSpeed = 2.0
gameTable.basicStinkieRange = 50

gameTable.basicHolyBoneHP = 5
gameTable.basicHolyBoneAttack = 0
gameTable.basicHolyBoneAttackSpeed = 3.0
gameTable.basicHolyBoneRange = 100
gameTable.basicHolyBoneHeal = 1



function getTable()
  generalTable = {}
  
  
  --basic components
  generalTable.ChasingComp = false
  generalTable.SeperationComp = false
  generalTable.FollowingComp = false
  generalTable.MeleeAttackComp = false
  generalTable.KeyboardComp = false
  generalTable.RecruitComp = false
  
  --pooled components
  generalTable.ActionFlagComp = false
  generalTable.AnimComp = false
  generalTable.AnimCompName = nil
  generalTable.CombatComp = false
  generalTable.DomainComp = false
  generalTable.DomainCompRadius = nil
  generalTable.HealComp = false
  generalTable.HordeStatusComp = false
  generalTable.KineticComp = false
  generalTable.KineticCompMaxSpeed = nil
  generalTable.ZombieSensorComp = false
  generalTable.WanderingComp = nil
  generalTable.WanderingCompInterval = 15
  
  -- combat statistics
  generalTable.hp = nil
  generalTable.attack = nil
  generalTable.attackSpeed = nil
  generalTable.range = nil
  generalTable.heal = nil
  -- 0/1/2    neutral/human/player
  generalTable.alliance = 2
  generalTable.x = nil
  generalTable.y = nil
  
  --others
  generalTable.ZombieCatagory = nil
  generalTable.isPlayer = false
  generalTable.StinkieNum = 0
  generalTable.ChuckerNum = 0
  generalTable.HolyBoneNum = 0
  generalTable.belongToPlayer = false
  
  --basic zombie statistics
  generalTable.chuckerHP = generalTable.basicChuckerHP
  generalTable.chuckerAttack = generalTable.basicChuckerAttack
  generalTable.chuckerAttackSpeed = generalTable.basicChuckerAttackSpeed
  generalTable.chuckerRange = generalTable.basicChuckerRange

  generalTable.stinkieHP = generalTable.basicStinkieHP
  generalTable.stinkieAttack = generalTable.basicStinkieAttack
  generalTable.stinkieAttackSpeed = generalTable.basicStinkieAttackSpeed
  generalTable.stinkieRange = generalTable.basicStinkieRange

  generalTable.holyBoneHP = generalTable.basicHolyBoneHP
  generalTable.holyBoneAttack = generalTable.basicHolyBoneAttack
  generalTable.holyBoneAttackSpeed = generalTable.basicHolyBoneAttackSpeed
  generalTable.holyBoneRange = generalTable.basicHolyBoneRange
  generalTable.holyBoneHeal = generalTable.basicHolyBoneHeal
  
  --functions
  generalTable.StinkieFunc = nil
  generalTable.ChuckerFunc = nil
  generalTable.HolyBoneFunc = nil
  
  
  return generalTable
end

function createZombie(BELONG )
  table = getTable()
  --basic components
  table.ChasingComp = true
  table.SeperationComp = true
  table.FollowingComp = true
  
  table.belongToPlayer = BELONG
  --pooled components
  table.CombatComp = true
  table.AnimComp = true
  table.ActionFlagComp = true
  table.KineticComp = true
  table.KineticCompMaxSpeed = gameTable.maxSpeed + math.random(-30,30)
  

  table.DomainComp = true
  
  if ( not BELONG) then
  table.x = math.random(0,gameTable.worldWidth)
  table.y = math.random(0,gameTable.worldHeight)
  table.WanderingComp = true
  end
  
  return table
end

function createStinkie(HP, ATTACK, ATTACKSPEED, RANGE, ALLIANCE, BELONG)
  table = createZombie(BELONG)
  table.hp = HP
  table.attack = ATTACK
  table.attackSpeed = ATTACKSPEED
  table.range = RANGE  
  table.MeleeAttackComp = true

  --others
  table.AnimCompName = "basic_zombie"
  table.ZombieCatagory = 1
  table.alliance = ALLIANCE
  return table
end

function createBasicStinkie(BELONG)
	return createStinkie(gameTable.basicStinkieHP,gameTable.basicStinkieAttack,gameTable.basicStinkieAttackSpeed,gameTable.basicStinkieRange,0,BELONG)
end

function createScalingStinkie(BELONG)
  return createStinkie(10+(gameTable.time / 30)*gameTable.difficulty,  2+(gameTable.time / 60)*gameTable.difficulty, 2.0-(.001*gameTable.time*gameTable.difficulty),10,2,BELONG)
end

function createChucker(HP, ATTACK, ATTACKSPEED, RANGE,ALLIANCE,BELONG)
  table = createZombie(BELONG)
  table.hp = HP
  table.attack = ATTACK
  table.attackSpeed = ATTACKSPEED
  table.range = RANGE  
  table.AnimCompName = "chucker"
  
  --others
  table.ZombieCatagory = 3
  table.alliance = ALLIANCE
  return table
end

function createBasicChucker(BELONG)
	return createChucker(gameTable.basicChuckerHP,gameTable.basicChuckerAttack,gameTable.basicChuckerAttackSpeed,gameTable.basicChuckerRange,0,BELONG)
end

function createScalingChucker(BELONG )
  return createChucker(7+(gameTable.time / 30)*gameTable.difficulty, 1+(gameTable.time / 60)*gameTable.difficulty, 1.5-(.001*gameTable.time*gameTable.difficulty), 100,2,BELONG)
end



function createHolyBone(HP, ATTACK, ATTACKSPEED, RANGE, HEAL,ALLIANCE,BELONG)
   table = createZombie(BELONG)
  table.hp = HP
  table.attack = ATTACK
  table.attackSpeed = ATTACKSPEED
  table.range = RANGE  
  table.heal = HEAL
  
  --others
  table.AnimCompName = "healer"
  table.HealComp = true
  table.ZombieCatagory = 2
  table.alliance = ALLIANCE
  return table
end

function createBasicHolyBone(BELONG)
	return createHolyBone(gameTable.basicHolyBoneHP,gameTable.basicHolyBoneAttack,gameTable.basicHolyBoneAttackSpeed,gameTable.basicHolyBoneRange,gameTable.basicHolyBoneHeal,0,BELONG)
end

function createScalingHolyBone(BELONG)
  return createHolyBone(5+(gameTable.time / 30)*gameTable.difficulty,0,3-(.001*gameTable.time*gameTable.difficulty),100,1 +(gameTable.time / 120)*gameTable.difficulty,2,BELONG)
end



function createPlayer(isHuman)
  player = getTable()
  player.isPlayer = true
  
  --pooled Components
  player.AnimComp = true
  player.KineticComp = true
  player.KineticCompMaxSpeed = gameTable.maxPlayerSpeed
  player.DomainComp = true
  player.DomainCompRadius = 50
  player.HordeStatusComp = true
  
  if (isHuman) then 
    player.KeyboardComp = true
    player.RecruitComp = true;
    player.x = gameTable.worldWidth / 2
    player.y = gameTable.worldHeight / 2
    player.AnimCompName = "swiss"
    player.StinkieNum = 1
    player.alliance = 1
    --setting horde statistics
    player.stinkieHP=gameTable.stinkieHP
    player.stinkieAttack = gameTable.stinkieAttack
    player.stinkieAttackSpeed = gameTable.stinkieAttackSpeed
    player.stinkieRange = gameTable.stinkieRange
    
    player.chuckerHP = gameTable.chuckerHP
    player.chuckerAttack = gameTable.chuckerAttack
    player.chuckerAttackSpeed = gameTable.chuckerAttackSpeed
    player.chuckerRange = gameTable.chuckerRange
    
    player.holyBoneHP = gameTable.holyBoneHP
    player.holyBoneAttack = gameTable.holyBoneAttack
    player.holyBoneAttackSpeed = gameTable.holyBoneAttackSpeed
    player.holyBoneRange = gameTable.holyBoneRange
    player.holyBoneHeal = gameTable.holyBoneHeal
    

  else 
    player.x = math.random(0,gameTable.worldWidth)
    player.y = math.random(0,gameTable.worldHeight)
    --to be changed to actual name for animation of other horde players
--    player.AnimCompName = "otherSwiss"
    player.AnimCompName = "swiss"
    player.WanderingComp = true
    player.ActionFlagComp = true
    player.alliance = 2
    player.StinkieNum = 1+gameTable.difficulty*(gameTable.time/30)*1
    player.ChuckerNum = gameTable.difficulty*(gameTable.time/55)*1
    player.HolyBoneNum = gameTable.difficulty*(gameTable.time/80)*1
    
        --setting horde statistics
    player.stinkieHP=10+(gameTable.time / 30)*gameTable.difficulty
    player.stinkieAttack = 2+(gameTable.time / 60)*gameTable.difficulty
    player.stinkieAttackSpeed = 2.0 -(.001*gameTable.time*gameTable.difficulty)
    player.stinkieRange = 10
    
    player.chuckerHP = 7+(gameTable.time / 30)*gameTable.difficulty
    player.chuckerAttack = 1+(gameTable.time / 60)*gameTable.difficulty
    player.chuckerAttackSpeed = 1.5-(    .001*gameTable.time*gameTable.difficulty)
    player.chuckerRange = 100
    
    player.holyBoneHP = 5+(gameTable.time / 30)*gameTable.difficulty
    player.holyBoneAttack = 0
    player.holyBoneAttackSpeed = 3-(.001*gameTable.time*gameTable.difficulty)
    player.holyBoneRange = 100
    player.holyBoneHeal = 1 +(gameTable.time / 120)*gameTable.difficulty
    
    
    
  end
  
      player.StinkieFunc = function ()
      return createStinkie(player.stinkieHP,player.stinkieAttack, player.stinkieAttackSpeed,player.stinkieRange,  player.alliance,true) 
    end
    player.ChuckerFunc = function()
      return createChucker(player.stinkieHP,player.stinkieAttack, player.stinkieAttackSpeed,player.stinkieRange,player.alliance,true) 
    end
    player.HolyBoneFunc = function()
      return createHolyBone(player.stinkieHP,player.stinkieAttack, player.stinkieAttackSpeed,player.stinkieRange,player.holyBoneHeal, player.alliance,true) 
    end
  
  return player
end
player = createPlayer(true)
basicChucker = createBasicChucker()
scalingChucker = player.ChuckerFunc()
print(basicChucker.hp,scalingChucker.hp)
print(basicChucker.attack,scalingChucker.attack)
print(basicChucker.attackSpeed,scalingChucker.attackSpeed)
print(basicChucker.heal,scalingChucker.heal)
print(basicChucker.DomainComp,scalingChucker.DomainCompRadius)
print(player.AnimCompName)
print(player.StinkieNum)
testStinkie=player.StinkieFunc()
print(testStinkie.AnimCompName)
print(testStinkie.x, testStinkie.y)






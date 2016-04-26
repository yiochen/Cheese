--dynamic zombie creating based on how much killed?
--time is in seconds elapsed?
--difficulty 1/2/3   easy/med/hard
gameTable = {difficulty = 1, time = 1}
gameTable.worldWidth = 700
gameTable.worldHeight = 700

function createBasicStinkie()
	table = {hp = 10, attack = 2, attackSpeed = 2.0, range =10}
  table.AnimComp = "basic_zombie"
  table.catagory = 1
  table.ChasingComp = true
  table.SeperationComp = true
  table.FollowingComp = true
  table.HealComp = false
	return table
end

function createStinkie( difficult,  timeElapsed)
	table = {hp = 10+(timeElapsed / 30)*difficult, attack = 2+(timeElapsed / 60)*difficult, attackSpeed = 2.0-(.001*timeElapsed*difficult), range =10}
  table.AnimComp = "basic_zombie"
  table.catagory = 1
  table.ChasingComp = true
  table.SeperationComp = true
  table.FollowingComp = true
  table.HealComp = false
	return table
end

function createBasicChucker()
	table = {hp = 7, attack = 1, attackSpeed = 1.5, range =100}
  table.AnimComp = "chucker"
  table.catagory = 3
  table.ChasingComp = true
  table.SeperationComp = true
  table.FollowingComp = true
  table.HealComp = false
	return table
end
function createChucker( difficult,  timeElapsed)
	table = {hp = 7+(timeElapsed / 30)*difficult, attack = 1+(timeElapsed / 60)*difficult, attackSpeed = 1.5-(.001*timeElapsed*difficult), range =100}
  table.AnimComp = "chucker"
  table.catagory = 3
  table.ChasingComp = true
  table.SeperationComp = true
  table.FollowingComp = true
  table.HealComp = false
	return table
end

function creatBasicHolyBone()
	table = {hp = 5, attack = 0, attackSpeed = 3, range =100, heal =1}
  table.AnimComp = "healer"
  table.catagory = 2
  table.ChasingComp = true
  table.SeperationComp = true
  table.FollowingComp = true
  table.HealComp = true
	return table
end
function createHolyBone( difficult,  timeElapsed)
	table = {hp = 5+(timeElapsed / 30)*difficult, attack = 0, attackSpeed = 3-(.001*timeElapsed*difficult), range =100, heal = 1 +(timeElapsed / 120)*difficult}
  table.AnimComp = "healer"
  table.catagory = 2
  table.ChasingComp = true
  table.SeperationComp = true
  table.FollowingComp = true
  table.HealComp = true
	return table
end

function createPlayer(isHuman)
  player = {stinkieNum = 1 + gameTable.difficulty*(gameTable.time/30)*1, chuckerNum = gameTable.difficulty*(gameTable.time/55)*1, healerNum = gameTable.difficulty*(gameTable.time/80)*1}
  player.stinkieFunc = createStinkie(gameTable.difficulty,gameTable.time)
  player.chuckerFunc = createChucker(gameTable.difficulty,gameTable.time)
  player.holyBoneFunc = createHolyBone(gameTable.difficulty,gameTable.time)
  
  player.KineticComp = true
  player.maxSpeed = 100.0
  player.AnimComp = true
  player.DomainComp = true
  player.DomainRadius = 50
  player.HordeStatusComp = true
  if (isHuman) then 
    player.KeyboardComp = true
    player.x = 0
    player.y = 0
    player.name = "swiss"
  else player.KeyboardComp = false
    player.x = math.random(0,worldWidth)
    player.y = math.random(0,worldHeight)
    player.name = "otherSwiss"
    --to be changed to actual name for animation of other horde players
  end
  
  return player
end





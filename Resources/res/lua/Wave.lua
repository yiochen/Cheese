--wave
--a wave contains information about the enermies that will be spawn at the same time

require "Entity"
require "Player"
require "Zombie"
require "Object"

WAVE_CA={
  PREP=0,
  NORMAL=1,
  FINAL=2,
  NONE=3
}

  
Wave=createType("Wave", Object)

Wave:addMembers({
    category=WAVE_CA.PREP,
    maxTime=60, --by default, player should finish the wave in maximum 60 seconds. If failed, the second wave will come
    waveStatus=WAVE_CA.NORMAL,
    playerList={count=0},
    zombieList={count=0}
  })

function Wave:push(entity)
  if (entity.__typename == Player.__typename)
  then
    self.playerList[self.playerList.count]=entity
    return self
  end
  if (entity.__typename == Zombie.__typename)
  then
    self.zombieList[self.zombieList.count]=entity
    return self
  end
  assert(false) --the entity is not a player or zombie. cannot be pushed
end

  

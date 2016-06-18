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
    playerList={count=0},
    zombieList={count=0}
  })

function Wave:new()
  self.playerList={count=0}
  setmetatable(self.playerList,{
    __tostring=function(p)
      local result="\n"
      for key, value in pairs(p)
      do
        result=result.."\t"..tostring(value).."\n"
      end
      return result
    end
    }
  )
  self.zombieList={count=0}
  setmetatable(self.zombieList,{
    __tostring=function(p)
      local result="\n"
      for key, value in pairs(p)
      do
        result=result.."\t"..tostring(value).."\n"
      end
      return result
    end
    }
  )  
end

function Wave:push(entity)
  if (entity.__typename == Player.__typename)
  then
    self.playerList[self.playerList.count]=entity
    self.playerList.count=self.playerList.count+1
    return self
  end
  if (entity.__typename == Zombie.__typename)
  then
    self.zombieList[self.zombieList.count]=entity
    self.zombieList.count=self.zombieList.count+1
    if (entity.player)
    then
      entity.player:push(entity)
    end
    return self
  end
  assert(false) --the entity is not a player or zombie. cannot be pushed
end




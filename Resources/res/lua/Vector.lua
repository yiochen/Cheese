--Vector type
require "Object"

function regulizeDeg(x)
  while (x>360)
  do
    x=x-360
  end
  while (x<0)
  do
    x=x+360
  end
  return x;
end

function rad2deg(x)
  return regulizeDeg(x/math.pi*180.0)
end
function deg2rad(x)
  return regulizeDeg(x)*math.pi/180.0
end

Vector=createType("Vector",Object)

Vector:addMembers({
    x=0,
    y=0,
  })

--member fields
function Vector:new(x, y)
  self.x=x
  self.y=y
end

do
  local meta=getmetatable(Vector)
 
  --Vector arithmatic operation
  function meta:__add( v )
      return Vector(self.x + v.x, self.y+ v.y)
  end
  
  function meta:__sub( v )
      return Vector(self.x - v.x, self.y - v.y)
  end
  --dot product
  function meta:__mul( v )
      return self.x * v.x + self.y * v.y
  end
  
  function meta:__tostring()
      return ("<%g, %g>"):format(self.x, self.y)
  end
end

function Vector:scale(factor)
    return Vector(self.x*factor, self.y*factor)
end

function Vector:norm()
    local mag=self:mag()
    return Vector(self.x/mag, self.y/mag)
end

--rotate counter clockwise
function Vector:rotate(deg)
    local rad=deg2rad(deg)
    local sin=math.sin(rad)
    local cos=math.cos(rad)
    return Vector(self.x*cos-self.y*sin,self.y*cos+self.x*sin)
end
  
function Vector:mag()
    return math.sqrt( self * self )
end


function Vector:angle()
    local x=self.x
    local y=self.y
  
    if (x==0 and y>=0)then return 90.0 end
    if (x==0 and y<0)then return 270.0 end
    if (x>0 and y==0)then return 0.0 end
    if (x<0 and y==0)then return 180.0 end
    
    if (y>0 and x>0)
    then
        return rad2deg(math.atan(y/x))
    end
    if (y>0 and x<0)
    then
        return regulizeDeg(rad2deg(math.atan(y/x))+180.0)
    end
    if (y<0 and x<0)
    then
        return regulizeDeg(rad2deg(math.atan(y/x))+180.0)
    end
      
    
    if (y<0 and x>0)
    then
        return regulizeDeg(rad2deg(math.atan(y/x))+360.0)
    end
    
end

--v=Vector(10,19)
--print(v:angle())
--v2=v:clone()
--v2=v2:scale(10):norm()+Vector(10,20)


--print(v)
--print(v2)

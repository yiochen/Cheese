--Object Oriented

Shape={
  hello=5}
Shape.__index=Shape

function Shape.new()
  local self=setmetatable({}, Shape)
  --self.posX=10
  self.posY=20
  return self
end
ShapeCp={}
ShapeCp.new=Shape.new
ShapeCp.posX=30
Shape.__index=ShapeCp



function Shape.print()
  print("this is a print without self")
end

function Shape.printSelf(self)
  print("this is a print with self", self.posX, self.posY)
end

Rect={}
--Rect.__index=Rect
setmetatable(Rect,{
    __index=Shape
  })


local shape=Shape.new()
print(shape.posX)
print(shape.hello)
--local shape2=shape.new()
--print(shape2.posX)
--print(shape.second)
--shape.print()
--shape:print()
----shape.printSelf() --this would fail, self is nil
--shape:printSelf()

--local rect=Rect.new()
--print(rect.posX)

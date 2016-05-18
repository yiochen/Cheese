--Object class
--base class of all objects

function isBasicType(value)
  return type(value)=="number" or type(value)=="boolean" or type(value)=="nil" or type(value)=="string"
end

function createType(typename, base)
  local Cls={}
  local meta={}
  --copy everything from the base to Cls
  --copy everything from base's meta to meta
  if (base)
  then
    for key, value in pairs(base)
    do
      Cls[key]=value
    end--for base 
    local basemeta=getmetatable(base)
    if (basemeta)
    then
      --copy the meta table of base to meta
      for key, value in pairs(basemeta)
      do
        meta[key]=value
      end--for basemeta
      meta.base=base--can get base from meta
    end--if basemeta
  end--if base
  
  --new function for initialization
  function Cls:new(...)
    print("creatign object")
  end
  
  --assign basic meta
  
  meta.__typename=typename
  meta.__index=meta
  meta.__call=function(cls,...)
      local self={}
      for key, value in pairs(cls)
      do
        self[key]=value
      end
      setmetatable(self, meta)
      
      self.new(self,...)
      return self
    end--__call function
    
  meta.__tostring=function(p)
    print(p.__typename.." {")
    for key, value in pairs(p)
    do
      print("  ",key,value)
    end
    print("}")
  end--tostring
  setmetatable(Cls, meta)
  return Cls
end--createType


Object=createType("Object", nil)--no base class

function Object:is(cls)
  local meta=getmetatable(self)
  while (meta and cls)
  do
    if (meta.__typename and cls.__typename and meta.__typename==cls.__typename)
    then
      
      return true
    end--if
    if (meta.base)
    then
      meta=getmetatable(meta.base)
    else
      meta=nil
    end
  end
  return false
end

--TestCls=createType("TestCls",nil)
--TestObject=createType("TestObject", Object)

--object=Object()
--testcls=TestCls()
--testObj=TestObject()


--print(object:is(Object))
--print(object:is(TestCls))
--print(testObj:is(Object))
--print(testObj:is(TestCls))
--print(testObj:is(TestObject))

  




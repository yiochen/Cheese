--item

require "Entity"
ITEM_CA={
  ITEM_NONE=0,
	ITEM_ATTACK=1,
	ITEM_SPEED=2,
	ITEM_HEALTH=3,
	ITEM_INVIN=4
}

Item=createType("Item", Entity)
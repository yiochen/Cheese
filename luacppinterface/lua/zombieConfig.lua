
--dynamic zombie creating based on how much killed?

function createStinkie()
	stinkie = {hp = 10, attack = 1, attackSpeed = 2.0}
	stinkie.kinetic = "true"
	return stinkie
end

function createChucker()
	chucker = {hp = 7, attack = 1, attackSpeed = 1.5}
	chucker.kinetic = "true"
	return chucker
end


local stink = createStinkie()
print(stink.hp,stink.attack, stink.attackSpeed, stink.kinetic)


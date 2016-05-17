# Cheese
Game logo
![logo][logo]

Team logo
![team][team]

## Scene design
![menu](https://github.com/yiochen/Cheese/blob/master/Resources/res/Assets/Images/EXAMPLE.png?raw=true)
## System requirement
This project is built on Window using Visual Studio Community 2015. Following tool are required for working and contributing to this project.  
- python 2.7
- Visual Studio Community 2015
- [Cocos Studio 3.10][cocos]
- Cocos2d-x (downloaded together with Cocos Studio)

## how to contribute
1. You can help with the documentation
2. You can help tune the zombie stats in lua file. Balancing is a important part in our game. All the stats of characters are saved in lua files and will be dynamically read in during runtime.
3. After you understand the system (yeah, the code is very messy), you can start implementing some logic. Look at the github issue for the things that need to be fixed or implemented.
4. Create graphics. Our game still needs a lot of graphic assets, from menu to different character spritesheets.

## build process
1. Make sure you have all the required software set up.
2. Clone the project to where you want it to be
3. Open up Cocos, click "Import Project", choose the root folder of the cloned repository.
4. Create/switch to your personal branch
5. Use Cocos Studio to edit the scene or use Visual Studio to implement game logic.
6. When you are done editing the scene. click "publish resource" to export csb file (which is a binary file type that can be read using cocos2d-x engine)
6. Work on the game logic in visual studio 2015.  

## Where to Learn Cocos2d -x
Cocos2d-x provides very good documentation. Please go to [get started page](http://www.cocos2d-x.org/learn) to learn more about Cocos2d-x.

## about box2d angle

	Vec2 a.angle(c,d)

This will get the smaller angle between c, and d in radian. The result has nothing to do with a

	Vec2 a.getAngle()

This will get the angle between a and x-positive axis. counter clockwise (a rotates from x-positive and up) is positive, clockwise is negative. 180 degree is positive (pi)  
Following are some examples

	Vec2 a = Vec2(10.0f, 0.0f); //horizontal left vector, angle=0
	Vec2 b = Vec2(0.0f, 10.0f);//vertical up vector angle=pi/4
	Vec2 c = Vec2(-10.0f, 10.0f);//angle =3pi/4
	Vec2 d = Vec2(0.0f, -10.0f);//angle=-pi/4
	Vec2 f = Vec2(-10.0f, -10.0f);//angle=-3pi/4
	Vec2 g = Vec2(-10.0f, 0.0f);//angle=pi


## Class Overview
This project adopt a way similar to an Entity Component Framework to prevent over abstraction. Basically each object in the game is an Entity. Each
entity can hold some components. There is no difference between a meelee zombie object and a range zombie object. The only difference is that they hold
different components. Think about components as both attribute and behavior. To read more about Entity Component Framework, visit this [page][ECS].
Following are some of the important classes.

### World
World is the most important class. It contains all the game objects in the game. It will also update all the objects every frame.
### Entity
Entity is the super class of all possible game objects in the game (such as zombie, swiss, bullet, items). Every entity has a sprite, even the invisible entity has an empty sprite. The sprite will be created and
### Zombie
Zombie extends Entity. All zombie has a leader.
### Player
Player extends Entity. Player is the leader of a zombie horde. The strayed zombie also has an invisible player leader.
### Item
Item extends Entity. Every non living thing is the game is a item, for example, bullet, medicine, rewards.

**important** Zombie, Player, and Item cannot be extend anymore, to make different game object, add components to them.  

### Component
Components are attribute or behavior of an entity
### PooledComponent
Extends Component. It will be recycled when removed from game.
### EntityRunner
EntityRunner will be called by world on each frame. It will gather all the entities that has the components it interested in, and perform some operation.



[logo]: https://github.com/yiochen/Cheese/blob/master/Resources/res/Assets/Images/Logo.png?raw=true
[team]:https://github.com/yiochen/Cheese/blob/master/Resources/res/Assets/Images/Team.png?raw=true
[cocos]:http://www.cocos2d-x.org/download
[ECS]:http://www.gamedev.net/page/resources/_/technical/game-programming/understanding-component-entity-systems-r3013

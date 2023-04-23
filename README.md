# endless-runner
Futuregames assignment - Endless Runner in Unreal

# Project Settings
- Blank, No Starter Content, C++

![image](https://user-images.githubusercontent.com/17746816/233835677-4fdd1e05-0189-4275-bd91-4d8db25ff4fe.png)
![UnrealEditor_xW57tjZvR8](https://user-images.githubusercontent.com/17746816/233839406-9e097a95-22cb-4480-8c5e-46fb5b425fe2.gif)

You can control the speed of the panning in code in the [PlatformManager](https://github.com/addeponkeN/endless-runner/blob/part1/Source/PonkRunner/PlatformManager.cpp) by calling the "SetTexturePanningSpeed(float speed)" function.

# Instructions

## - Spawning platforms over a pre-defined area of the screen which scroll past the player at a particular rate

Instead of spawning platforms im placing static platforms with panning textures. This will give the effect that the platforms are moving at a very low cost.

(this is the only blueprint code in the project)

![image](https://user-images.githubusercontent.com/17746816/233837671-b53b601b-77fc-48de-a419-3f5924921833.png)




## - Spawning projectiles/enemies which spawn over a pre-defined area of the screen which scroll past the player at a particular rate 

I have 2 obstacles so far - [Wall](https://github.com/addeponkeN/endless-runner/blob/part1/Source/PonkRunner/WallObstacle.cpp) and Rock, which are derived from (or is) [ObstacleBase](https://github.com/addeponkeN/endless-runner/blob/part1/Source/PonkRunner/ObstacleBase.cpp). The player can shoot the rock with a weapon to destroy it for extra score. The wall cannot be destroyed.
If the player is hit by either they lose 1 life.

Walls and rocks are spawned by [WallSpawner](https://github.com/addeponkeN/endless-runner/blob/part1/Source/PonkRunner/WallSpawner.cpp) and [ObstacleSpawner](https://github.com/addeponkeN/endless-runner/blob/part1/Source/PonkRunner/ObstacleSpawner.cpp) which are derived from [SpawnerBas](https://github.com/addeponkeN/endless-runner/blob/part1/Source/PonkRunner/SpawnerBase.cpp)

### Pooling

Obstacles and Bullets are pooled using the generic [ActorPool](https://github.com/addeponkeN/endless-runner/blob/part1/Source/PonkRunner/ActorPool.h)

![image](https://user-images.githubusercontent.com/17746816/233838267-df87832d-4ede-4e80-b03d-8861615750f5.png)

How a bullet is created/spawned:

![image](https://user-images.githubusercontent.com/17746816/233838763-b2e7374c-6acd-4733-a4a7-1cee58a250b4.png)


Before I can spawn a type with the pool you need to initialize it with a template object

![image](https://user-images.githubusercontent.com/17746816/233838969-4ebd1442-1c24-4554-8859-4015d0f4aaf2.png)





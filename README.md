# endless-runner
Futuregames assignment - Endless Runner in Unreal

# Project Settings
- Blank, No Starter Content, C++

![image](https://user-images.githubusercontent.com/17746816/233835677-4fdd1e05-0189-4275-bd91-4d8db25ff4fe.png)


# Instructions

### - Spawning platforms over a pre-defined area of the screen which scroll past the player at a particular rate

Instead of spawning platforms im placing static platforms with panning textures. This will give the effect that the platforms are moving at a very low cost.

(this is the only blueprint code in the project)

![image](https://user-images.githubusercontent.com/17746816/233837671-b53b601b-77fc-48de-a419-3f5924921833.png)



### - Spawning projectiles/enemies which spawn over a pre-defined area of the screen which scroll past the player at a particular rate 

I have 2 obstacles so far - Wall and Rock. The player can shoot the rock with a weapon to destroy it for extra score. The wall cannot be destroyed.
If the player is hit by either they lose 1 life.
Walls and rocks are spawned by [WallSpawner](https://github.com/addeponkeN/endless-runner/blob/part1/Source/PonkRunner/WallSpawner.cpp) and [ObstacleSpawner](https://github.com/addeponkeN/endless-runner/blob/part1/Source/PonkRunner/ObstacleSpawner.cpp) which are derived from [SpawnerBas](https://github.com/addeponkeN/endless-runner/blob/part1/Source/PonkRunner/SpawnerBase.cpp)

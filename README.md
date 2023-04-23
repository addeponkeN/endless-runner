# DOWNLOADS

### [SOURCE](https://github.com/addeponkeN/endless-runner/archive/refs/tags/part1_release.zip) / [RELEASE](https://github.com/addeponkeN/endless-runner/releases/download/part1_release/EndlessRunner_Part1.zip)


# Project Settings
- Blank, No Starter Content, C++

![image](https://user-images.githubusercontent.com/17746816/233835677-4fdd1e05-0189-4275-bd91-4d8db25ff4fe.png)


# Instructions

## 1. Spawning platforms over a pre-defined area of the screen which scroll past the player at a particular rate

Instead of spawning platforms I'm placing static platforms with panning textures. This will give the effect that the platforms are moving at a very low cost.

(this is the only blueprint graph in the project)

![image](https://user-images.githubusercontent.com/17746816/233837671-b53b601b-77fc-48de-a419-3f5924921833.png)
![UnrealEditor_xW57tjZvR8](https://user-images.githubusercontent.com/17746816/233839406-9e097a95-22cb-4480-8c5e-46fb5b425fe2.gif)

You can control the speed of the panning in code in the [PlatformManager](https://github.com/addeponkeN/endless-runner/blob/part1/Source/PonkRunner/PlatformManager.cpp) by calling the "SetTexturePanningSpeed(float speed)" function.





## 2. Spawning projectiles/enemies which spawn over a pre-defined area of the screen which scroll past the player at a particular rate 

I have 2 obstacles so far - [Wall](https://github.com/addeponkeN/endless-runner/blob/part1/Source/PonkRunner/WallObstacle.cpp) and Rock (Rock is a BP derived from ObstacleBase), which are derived from [ObstacleBase](https://github.com/addeponkeN/endless-runner/blob/part1/Source/PonkRunner/ObstacleBase.cpp). The player can shoot the rock with a weapon to destroy it for extra score. The wall cannot be destroyed.
If the player is hit by either they lose 1 life.

Walls and rocks are spawned by [WallSpawner](https://github.com/addeponkeN/endless-runner/blob/part1/Source/PonkRunner/WallSpawner.cpp) and [ObstacleSpawner](https://github.com/addeponkeN/endless-runner/blob/part1/Source/PonkRunner/ObstacleSpawner.cpp) which are derived from [SpawnerBase](https://github.com/addeponkeN/endless-runner/blob/part1/Source/PonkRunner/SpawnerBase.cpp)

### Pooling

Obstacles and Bullets are pooled using the generic [ActorPool](https://github.com/addeponkeN/endless-runner/blob/part1/Source/PonkRunner/ActorPool.h)

![image](https://user-images.githubusercontent.com/17746816/233838267-df87832d-4ede-4e80-b03d-8861615750f5.png)

How a bullet is created/spawned:

![image](https://user-images.githubusercontent.com/17746816/233838763-b2e7374c-6acd-4733-a4a7-1cee58a250b4.png)


Before I can spawn a type with the pool you need to register/initialize it with a template object

![image](https://user-images.githubusercontent.com/17746816/233838969-4ebd1442-1c24-4554-8859-4015d0f4aaf2.png)


## 3. Increasing difficulty over time

Difficulty is a value between 0 and 1. The [DifficutlyManager](https://github.com/addeponkeN/endless-runner/blob/part1/Source/PonkRunner/DifficultyManager.cpp) will increment the value and broadcoast when it does. The spawners will listen to this broadcast and adjust the spawnrate with lerp(minRate, maxRate, difficulty).


## 4. Accumulated points which increase as time progresses and is saved in a high score list shown at startup

The [ScoreManager](https://github.com/addeponkeN/endless-runner/blob/part1/Source/PonkRunner/ScoreManager.cpp) only contains a score value and broadcasts an event when the score has been changed. Things like UI listens to this.

The [ScoreController](https://github.com/addeponkeN/endless-runner/blob/part1/Source/PonkRunner/RunnerScoreController.cpp) increments score periodically to the ScoreManager.

The [HighScoreManager](https://github.com/addeponkeN/endless-runner/blob/part1/Source/PonkRunner/HighScoreManager.cpp) handles all highscore entries, saving & loading. A highscore entry is added when the game is over (only if a name was specified). The highscore list is sorted and saved when a new entry is added.
The high scores are stored in a .txt file.


## 5. 3 lives in each game

The player object has a [HealthComponent](https://github.com/addeponkeN/endless-runner/blob/part1/Source/PonkRunner/HealthComponent.cpp) attached to it.
It is set to 3 lives in the editor. The [PonkRunnerGameModeBase](https://github.com/addeponkeN/endless-runner/blob/part1/Source/PonkRunner/PonkRunnerGameModeBase.cpp) listens to the player's HealthComponent ValueChanged event and if it's 0, the game state is set to GameOver.

## 6. Projectile to player collision

Currently the player class ([RunManCharacter](https://github.com/addeponkeN/endless-runner/blob/part1/Source/PonkRunner/RunManCharacter.cpp)) overloads the OnColliderOverlapBegin() function and does a check if its hit by an obstacle.
I'm changing this later so that the player will have an [ObstacleCollider/ObstacleReceiver](https://github.com/addeponkeN/endless-runner/blob/part1/Source/PonkRunner/ObstacleCollider.cpp) component attached to it. It will handle all collision with obstacles and broadcast an event that the player class will listen to.

## 7. Basic keyboard controls

Currently using the old deprecated input system.



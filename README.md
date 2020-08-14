# Wolf3D
## Project objective
  Write my own version of Wolfenstein 3D using the ray casting technique, a 3D representation of a maze in which a player can find his/her way.
## Skills to acquire and use
•	Fundamentals of C  
•	Algorithm elaboration  
•	Imperative programming  
•	Rigor  
•	Graphics  
•	Getting acquainted with the ray casting rendering technique
## How to run it? (works on Linux and MacOS)
•	git clone https://github.com/DaniilMD/Wolf3D.git «Folder name»  
•	cd «Folder name»  
•	make  
•	Run the program using executable "wolf3d" and a map model text file as an argument. (There is a special folder "maps/" in the project repository, which contains several maps to use)  
For example:  
```
./wolf3d maps/labyrinth
```
## What does it do?
It builds a 3D image on the screen which constantly updates. Here is an example:
  
![Screenshot from 2020-08-13 18-01-31](https://user-images.githubusercontent.com/48802453/90151211-25a73b80-dd8f-11ea-8a8e-959bb7da8743.png)
  
You can travel through the map using arrow keys to move, QE keys to rotate, F to open doors/use protals/destroy secret walls. Also, some coins can exist on the map. They can be picked up to raise your score when you finish the game.
  
![Screenshot from 2020-08-13 17-57-22](https://user-images.githubusercontent.com/48802453/90151014-ec6ecb80-dd8e-11ea-9395-620623e09cb4.png)
  
Rules of how to create a map are present in the repository under the name of "how_to_create_a_map" file.
## How it works

## Project evaluation result  
### Score 125/100  
Mandatory part  
100/100  
  
Bonus part  
25/25
  
Bonus funtionality:  
1) Floor and ceiling
  
![Screenshot from 2020-08-13 18-08-22](https://user-images.githubusercontent.com/48802453/90246506-783f3100-de3d-11ea-97e5-cc45654506c0.png)
  
2) Fog effect
  
![Screenshot from 2020-08-13 18-07-29](https://user-images.githubusercontent.com/48802453/90246613-ac1a5680-de3d-11ea-9fdb-103ffb7fc125.png)
  
3) Sprites (barrels, pillars, coins and lamps)
  
Barrels and pillars cannot be walked through  (one of the next bonuses)
![Screenshot from 2020-08-13 18-05-37](https://user-images.githubusercontent.com/48802453/90246615-acb2ed00-de3d-11ea-98ce-79f61c846ebe.png)
  
Lamps have no physics and can be walked under    
![Screenshot from 2020-08-14 14-47-09](https://user-images.githubusercontent.com/48802453/90247035-72961b00-de3e-11ea-88b2-4bcee876f633.png)
  
Coins are pickable (one of the next bonuses)  
  
![Screenshot from 2020-08-14 14-47-28](https://user-images.githubusercontent.com/48802453/90247796-0b796600-de40-11ea-8c33-6526ef629991.png)
  
  
4) Hitting sprites (not being able to pass through them)
  
Right there on the screenshot you can see (try to imagine) me ferociously hitting "W" key and i can't move forward, only shifting to the left.  
![Screenshot from 2020-08-14 14-47-54](https://user-images.githubusercontent.com/48802453/90247876-2d72e880-de40-11ea-82eb-319df50d50e5.png)

  
5) Hitting walls (not being able to pass through them)  
  
Same story with walls  
![Screenshot from 2020-08-14 15-17-33](https://user-images.githubusercontent.com/48802453/90248461-68295080-de41-11ea-94fe-1dc347f0e485.png)
  
6) Coin picking (and point counting)
  
Coin in front of me  
![Screenshot from 2020-08-14 14-48-37](https://user-images.githubusercontent.com/48802453/90248079-a3774f80-de40-11ea-8eb5-ef8850bb76a7.png)
  
Coin picked  
![Screenshot from 2020-08-14 14-48-38](https://user-images.githubusercontent.com/48802453/90248082-a40fe600-de40-11ea-8e5d-beafeb8e040c.png)

No coin left on the map  
![Screenshot from 2020-08-14 15-11-021](https://user-images.githubusercontent.com/48802453/90248087-a6724000-de40-11ea-9625-934ba9265511.png)
  
A point acquired ("Points: 3" in terminal shows that a coin has been picked)
![Screenshot from 2020-08-14 15-11-02](https://user-images.githubusercontent.com/48802453/90248090-a83c0380-de40-11ea-834a-d671f19899b0.png)

7) Minimap
  
Pressing "M" on a keyboard opens the minimap (pressing it again closes it), which shows your position on the map and the look of the map itself.  
![Screenshot from 2020-08-14 15-23-06](https://user-images.githubusercontent.com/48802453/90249088-82aff980-de42-11ea-83b8-cab30df227b9.png)
  
![Screenshot from 2020-08-14 15-23-48](https://user-images.githubusercontent.com/48802453/90249092-85125380-de42-11ea-887d-c2a92c81239a.png)
  
8) Doors (Pressing "F" in front of a door opens it and you can walk through)  
  
Closed door  
![Screenshot from 2020-08-14 15-30-25](https://user-images.githubusercontent.com/48802453/90249547-5648ad00-de43-11ea-9ef1-12bac57ba52d.png)
  
Door starts to open  
![Screenshot from 2020-08-14 15-30-08](https://user-images.githubusercontent.com/48802453/90249550-5779da00-de43-11ea-94b1-bc2436b8ba14.png)
  
Door is opened  
![Screenshot from 2020-08-14 15-30-30](https://user-images.githubusercontent.com/48802453/90249553-58127080-de43-11ea-9682-1b2abbe7973f.png)

9) Different levels (transferring between them through portals)
  
Find a portal on the map (if it exists). Come to it, press "F". If it is one of the three connected maps specially created (labyrinth->jojo->crosses), you'll be transferred to the next map in queue or finish the game (after the last map). Otherwise, you finish the game immidiately.  
![Screenshot from 2020-08-14 15-37-02](https://user-images.githubusercontent.com/48802453/90250097-3b2a6d00-de44-11ea-8dab-76d5590e4587.png)
  
![Screenshot from 2020-08-14 15-37-08](https://user-images.githubusercontent.com/48802453/90250099-3bc30380-de44-11ea-9f50-4f52e0eba6e1.png)
  
![Screenshot from 2020-08-14 15-43-51](https://user-images.githubusercontent.com/48802453/90250693-21d5f080-de45-11ea-801e-7ab3b03f50e7.png)

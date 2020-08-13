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
  
You can travel through the map using WASD keys to move, QE keys to rotate, F to open doors/use protals/destroy secret walls. Also, some coins can exist on the map. They can be picked up to raise your score when you finish the game.
  
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
2) Fog effect
3) Sprites
4) Hitting sprites (not being able to pass through them)
5) Coin picking (and point counting)
6) Hitting walls (not being able to pass through them)
7) Minimap
8) Doors
9) Different levels (transferring between them through portals)

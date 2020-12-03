# pa2-pacman

Console version of the classical game. Written in C++, uses the ncurses library to output characters to terminal. FIT CTU school project.  

Features: various ghost types, power-ups, bonuses, teleports, customizable maps...

## Screenshot

![Screenshot](https://user-images.githubusercontent.com/17980426/38249433-eb08e38e-374b-11e8-9305-f4a86a64e7b3.png)

## How to set up

1. Clone the repository, `cd` into it
2. Create a build directory and enter it: `mkdir build && cd build`
3. Run cmake (with the project root directory as argument): `cmake ..`
4. Build the project: `make`
5. Run the game with e.g. `pacman ../maps/1.pacmap 3` (arguments: file with map, difficulty)

## How to create a custom map

Create a normal text file and save it with the _.pacmap_ extension. You can get inspiration from the files in the _maps/_ directory. Symbol meaning:

* __H__ wall
* __(space)__ empty block
* __<__ player's starting position
* __o__ enemy spawn point
* __\\__ teleport
* __.__ powerup (invincibility)

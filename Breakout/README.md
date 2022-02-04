# README

## To be fair, this is a guide and reminder for me what I need to do

### Purpose

The objective of this solution is to create a clone of the legendary 
game Breakout, with the intention to complete the task I was given by the
recruiters at Gamepires Ltd, Zagreb. 

### Required features

* Reading level data from XML files
* Completely rendered graphics using textures for the paddle, bricks and the ball
* Game logic such as:
	* Collision detection
	* Tracking score and lives
	* Multi-HP bricks
	* The ball needs to increase in speed progressively 
	* There needs to be a possibility to load more levels
	* The paddle must be controlled by the mouse because of variable speed
* Sounds
* A tiny bit of game level design

And all of that using, of course, object oriented features, with best practices
both in performance and code readability

### Limitations

* Must be made in Visual Studio
* Must be organized so that all used libraries are contained within the project
* Cannot use any fancy frameworks 

### Implementations

*Libraries*

Some of the recommended libraries are already something I have worked with. Since SDL2
is given as an example, I use it for window and event handling, graphics, and sound.
XML parsing (God help me since I know nothing about XML files) is done using the tinyxml library.

*Game architecture*

Game architecture is described in a different file.
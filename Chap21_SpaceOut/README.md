In This chapter the GameEngine Sprite class gains the ability to spawn Sprites.
This is demonstrate with a game portraing the shoutout between aliens that
launches missiles to the player.

One of the big differency with the original code is that in the original code
the game related function and variables where globals, where in this version a
Game class was created.
The AlienSprite class identify which alien type is created by comparing the
Sprite bitmap address and the global alien bitmap sprite.
Those bitmaps are now member of the Game class, so to be access in the
AlienSprite class, they are now static members. 



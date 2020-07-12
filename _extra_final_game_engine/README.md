The game engine is build step by step, adding functionalities in each chapter.
This extra game engine contains the demo linked to the final game engine with some extra features:

* The game engine is seperated in his own directory and each
game includes the common game engine code.

* The game engine is from the last chapter of the book (Chapter 24), the games
from earlier chapters had been modified to match this version of the game
engine.

If the goal of the SDL2 rewrite was to have a code that matches the book.

The goal of this new engine is to have the game engine and demos open to
modifications and various enhancements, and expose the game engine API in a
definitive and usable way to new games.

Modifications are available in the github logs, but here is a brief log of some
changes:

* Game Engine uses namespace TYGP
* Renamed Bitmap class to Image
* Converted all bmp to png
* UFO program uses StarryBackground

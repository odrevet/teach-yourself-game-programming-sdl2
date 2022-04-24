In this chapter the game engine and the UFO game are upgraded with the
support of the joystick controller.
I was amaze that the original Windows exe worked fine on linux with wine and an
Xbox controler.

The UFO can be controled with the control pad, a button is mapped to
display/hide a flame under the UFO (no gameplay differances) and with
another button the UFO goes to "hyperspace" mode in which the UFO is teleported
at a random location for each game cycle. 

The SDL2 conversion in straightforward, the joystick is detected by the new
SDL2 GameController API build above the SDL2 Joystick API.

Also, a new function GameEngine::Run has been created, with most of the code
from the main function (the main loop).

#Key differances with the original code
* Uses SDL2 GameController API
* The main loop is in GameEngine::Run
* JOYSTATE constants are now in an enum.
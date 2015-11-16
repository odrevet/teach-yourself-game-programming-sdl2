
In this example, an icon is randomly drawn on the screen. The Screen is never
refreshed, so even if the icone is drawn once per game cycle, it appeare several
times.

Some minor adjustement has been made to the source code beside the SLD2 port.

a main.cpp file has been created for the main function, instead of having it in
the GameEngine.cpp file

Instead of having global functions in Skeleton.cpp an Interface IGame is
defined and implemented by a Game class.

From now on, only the main.cpp, Game.h and Game.cpp files will contain the game
specific code, every other files are part of the engine. 

in the main function, the following statements

```c++
  if (GameInitialize(hInstance))
  {
    // Initialize the game engine
    if (!GameEngine::GetEngine()->Initialize(iCmdShow))
      return FALSE;
```

has been replaced by

```c++
  const char* game_name = "Game skeleton";
  const char* game_icon = "res/Skeleton.ico";
  
  //Initialize or quit if an error occured
  if (!pGameEngine->Initialize(game_name, game_icon) ||
      !pGame->Initialize()){
    std::cout << "INIT ERR" << std::endl;
    return EXIT_FAILURE;
  }
```

The full main function is not anymore in an if brace,
You can also notice the pGame variable of type Game* instead of
global function as previously stated and the parameters are moved
from the constructor to Initialize. 

The activated / deactivated part is not implemented.
The game starts immediatly after the initialization

# key differences with the original code

* The GameEngine Class uses the singleton design pattern
* The main function is out of GameEngine.cpp
* Created IGame interface and Game Class
* Replaced GetTickCount With SDL_GetTicks
* Removed HInstance, replaced HWND by SDL_Window
* Converted the .ico to display to a .png
* Changed WIN32 types to standard types
 * renamed FALSE and TRUE to false and true
 * renamed BOOL to bool
 * LPSTR, TCHAR  are char* or char[]

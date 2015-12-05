#include <SDL.h>
#include <iostream>

#include "IGame.h"
#include "Game.h"
#include "GameEngine.h"

//-----------------------------------------------------------------
// Main function
//-----------------------------------------------------------------
int main (int argc, char* argv[])
{
  //get the game engine
  GameEngine *pGameEngine = GameEngine::GetEngine();
  
  //instantiate the game
  IGame *pGame = new Game;

  //assign the created game to the engine
  pGameEngine->m_game = pGame;
  
  const char* game_name = "Roids 2";
  const char* game_icon = "res/Roids.ico";
  int window_width = 500;
  int window_height = 400;

  //Initialize or quit if an error occured
  if (!pGameEngine->Initialize(game_name,
			       game_icon,
			       window_width,
			       window_height) ||
      !pGame->Initialize()){
    std::cout << "INIT ERR: " << SDL_GetError() << std::endl;
    return EXIT_FAILURE;
  }


  pGameEngine->Run();
    
  return EXIT_SUCCESS;
}


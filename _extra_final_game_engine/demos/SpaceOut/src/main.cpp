#include <SDL.h>
#include <iostream>

#include <IGame.h>
#include <GameEngine.h>

#include "Game.h"

using namespace TYGP;

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
  
  const char* game_name = "Space Out 4";
  const char* game_icon = "res/SpaceOut.ico";
  int window_width = 600;
  int window_height = 450;

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


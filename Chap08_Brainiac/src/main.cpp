#include <SDL.h>
#include <iostream>

#include "IGame.h"
#include "Game.h"
#include "GameEngine.h"

//-----------------------------------------------------------------
// Main function
//-----------------------------------------------------------------
int main(int argc, char *argv[])
{
  // instanciante the game
  IGame *pGame = new Game;

  // get the game engine and assign the game
  GameEngine *pGameEngine = GameEngine::GetEngine();
  pGameEngine->m_game = pGame;

  const char *game_name = "Brainiac";
  const char *game_icon = "res/Brainiac.ico";
  int window_width = 528;
  int window_height = 508;

  // Initialize or quit if an error occured
  if (!pGameEngine->Initialize(game_name,
                               game_icon,
                               window_width,
                               window_height) ||
      !pGame->Initialize())
  {
    std::cout << "INIT ERR" << std::endl;
    return EXIT_FAILURE;
  }

  pGameEngine->Run();

  return EXIT_SUCCESS;
}

#include <SDL.h>
#include <iostream>

#include <IGame.h>
#include <GameEngine.h>

#include "Game.h"

using namespace TYGP;

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

  const char *game_name = "SlideShow";
  const char *game_icon = "res/Slideshow.ico";
  int window_width = 640;
  int window_height = 480;

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

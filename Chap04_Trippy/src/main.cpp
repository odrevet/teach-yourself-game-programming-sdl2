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
  //instanciante the game
  IGame *pGame = new Game;

  //get the game engine
  GameEngine *pGameEngine = GameEngine::GetEngine();
  
  static int  iTickTrigger = 0;
  int         iTickCount;
  bool done = false;

  const char* game_name = "Trippy";
  const char* game_icon = "res/Trippy.ico";
  
  //Initialize or quit if an error occured
  if (!pGameEngine->Initialize(game_name, game_icon) ||
      !pGame->Initialize()){
    std::cout << "INIT ERR" << std::endl;
    return EXIT_FAILURE;
  }


  //start the game now
  pGameEngine->SetSleep(false);
  pGame->Start();
  
  // Enter the main message loop
  while (!done) {
    // Make sure the game engine isn't sleeping
    if (!pGameEngine->GetSleep()){
      // Check the tick count to see if a game cycle has elapsed
      iTickCount = SDL_GetTicks();
      if (iTickCount > iTickTrigger){
	iTickTrigger = iTickCount +
	  pGameEngine->GetFrameDelay();
	pGame->Cycle();
      }
    }
     
    pGameEngine->HandleEvent();

    // Paint the game
    pGame->Paint();
  }
  
  // End the game
  pGame->End();
    
  return EXIT_SUCCESS;
}


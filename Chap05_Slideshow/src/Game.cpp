//-----------------------------------------------------------------
// Game Skeleton Application
// C++ Source - Skeleton.cpp
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Game.h"

//-----------------------------------------------------------------
// Game Engine Functions
//-----------------------------------------------------------------

Game::~Game(){

}

bool Game::Initialize()
{
  //get the game engine
  GameEngine *pGameEngine = GameEngine::GetEngine();

  // Set the frame rate
  pGameEngine->SetFrameRate(1);
    
  return true;
}

void Game::Start()
{
  // Seed the random number generator
  srand(SDL_GetTicks());

  GameEngine *pGE = GameEngine::GetEngine();
  SDL_Renderer *renderer = pGE->GetRenderer();

  // Create and load the slide bitmaps
  this->_pSlides[0] = new Bitmap(renderer, "res/Image1.bmp");
  this->_pSlides[1] = new Bitmap(renderer, "res/Image2.bmp");
  this->_pSlides[2] = new Bitmap(renderer, "res/Image3.bmp");
  this->_pSlides[3] = new Bitmap(renderer, "res/Image4.bmp");
  this->_pSlides[4] = new Bitmap(renderer, "res/Image5.bmp");
  this->_pSlides[5] = new Bitmap(renderer, "res/Image6.bmp");

  // Set the first slide
  _iCurSlide = 0;  
}

void Game::End()
{
  // Cleanup the slide bitmaps
  for (int i = 0; i < _iNUMSLIDES; i++)
    delete this->_pSlides[i];
 
  // Cleanup the game engine
  GameEngine *pGameEngine = GameEngine::GetEngine();
  delete pGameEngine;
}

void Game::Activate()
{
}

void Game::Deactivate()
{
}

void Game::Paint()
{
  GameEngine* pGE = GameEngine::GetEngine();
  SDL_Renderer* renderer = pGE->GetRenderer();

  // Draw the current slide bitmap
  _pSlides[_iCurSlide]->Draw(renderer, 0, 0);

  // Force a repaint to draw the next slide
  SDL_RenderPresent(renderer);  
}

void Game::Cycle()
{ 
  static int iDelay = 0;

  // Establish a 3-second delay before moving to the next slide
  if (++iDelay > 3)
  {
    // Restore the delay counter
    iDelay = 0;

    // Move to the next slide
    if (++_iCurSlide == _iNUMSLIDES)
      _iCurSlide = 0;
  }  
  
}


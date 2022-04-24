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

Game::~Game()
{
}

bool Game::Initialize()
{
  // get the game engine
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
  this->_pSlides[0] = new Image(renderer, "res/Image1.png");
  this->_pSlides[1] = new Image(renderer, "res/Image2.png");
  this->_pSlides[2] = new Image(renderer, "res/Image3.png");
  this->_pSlides[3] = new Image(renderer, "res/Image4.png");
  this->_pSlides[4] = new Image(renderer, "res/Image5.png");
  this->_pSlides[5] = new Image(renderer, "res/Image6.png");

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
  GameEngine *pGE = GameEngine::GetEngine();
  SDL_Renderer *renderer = pGE->GetRenderer();

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

bool Game::HandleKeys()
{
  SDL_PumpEvents();
  const Uint8 *state = SDL_GetKeyboardState(NULL);

  // Q
  if (state[SDL_GetScancodeFromKey(SDLK_q)])
  {
    return true;
  }

  return false;
}

void Game::MouseButtonDown(int x, int y, bool bLeft)
{
}

void Game::MouseButtonUp(int x, int y, bool bLeft)
{
}

void Game::MouseMove(int x, int y)
{
}

void Game::HandleJoystick(JOYSTATE jsJoystickState)
{
}

bool Game::SpriteCollision(Sprite *pSpriteHitter,
                           Sprite *pSpriteHittee)
{
  return false;
}

void Game::SpriteDying(Sprite *pSprite)
{
}

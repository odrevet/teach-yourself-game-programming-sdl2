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
  pGameEngine->SetFrameRate(30);

  // Initialize the joystick

  return true;
}

void Game::Start()
{
  // Seed the random number generator
  srand(time(NULL));

  GameEngine *pGE = GameEngine::GetEngine();
  SDL_Renderer *renderer = pGE->GetRenderer();

  // Create and load the asteroid bitmap
  SDL_Color scTrans = {255, 0, 255, 255};
  _pAsteroidBitmap = new Bitmap(renderer, "res/Asteroid.bmp", &scTrans);

  // Create the starry background
  _pBackground = new StarryBackground(500, 400);

  // Create the asteroid sprites
  SDL_Rect rcBounds = {0, 0, 500, 400};
  Sprite *pSprite;
  pSprite = new Sprite(_pAsteroidBitmap, rcBounds, BA_WRAP);
  pSprite->SetNumFrames(14);
  pSprite->SetFrameDelay(1);
  pSprite->SetPosition(250, 200);
  pSprite->SetVelocity(-3, 1);
  pGE->AddSprite(pSprite);
  pSprite = new Sprite(_pAsteroidBitmap, rcBounds, BA_WRAP);
  pSprite->SetNumFrames(14);
  pSprite->SetFrameDelay(2);
  pSprite->SetPosition(250, 200);
  pSprite->SetVelocity(3, -2);
  pGE->AddSprite(pSprite);
  pSprite = new Sprite(_pAsteroidBitmap, rcBounds, BA_WRAP);
  pSprite->SetNumFrames(14);
  pSprite->SetFrameDelay(3);
  pSprite->SetPosition(250, 200);
  pSprite->SetVelocity(-2, -4);
  pGE->AddSprite(pSprite);
}

void Game::End()
{
  GameEngine *pGameEngine = GameEngine::GetEngine();

  // Cleanup the asteroid bitmap
  delete _pAsteroidBitmap;

  // Cleanup the background
  delete _pBackground;

  // Cleanup the sprites
  pGameEngine->CleanupSprites();

  // Cleanup the game engine
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
  GameEngine *pGameEngine = GameEngine::GetEngine();
  SDL_Renderer *renderer = pGameEngine->GetRenderer();

  // Draw the background
  _pBackground->Draw(renderer);

  // Draw the sprites
  pGameEngine->DrawSprites();

  SDL_RenderPresent(renderer);
}

void Game::Cycle()
{
  GameEngine *pGameEngine = GameEngine::GetEngine();

  // Update the background
  _pBackground->Update();

  // Update the sprites
  pGameEngine->UpdateSprites();
}

void Game::HandleKeys()
{
  SDL_PumpEvents();
  const Uint8 *state = SDL_GetKeyboardState(NULL);

  // Q
  if (state[SDL_GetScancodeFromKey(SDLK_q)])
  {
    exit(0);
  }
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

bool Game::SpriteCollision(Sprite *pSpriteHitter, Sprite *pSpriteHittee)
{
  return false;
}

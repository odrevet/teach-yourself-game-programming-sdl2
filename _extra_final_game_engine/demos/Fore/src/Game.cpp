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
  pGameEngine->SetFrameRate(30);

  return true;
}

void Game::Start()
{
  // Seed the random number generator
  srand(time(NULL));

  GameEngine *pGE = GameEngine::GetEngine();
  SDL_Renderer *renderer = pGE->GetRenderer();

  // Create and load the bitmaps
  _pForestImage = new Image(renderer, "res/Forest.png");
  SDL_Color scTransColor = {0xFF, 0x0, 0xFF, 0xFF};
  _pGolfBallImage = new Image(renderer, "res/GolfBall.png", &scTransColor);

  // Create the golf ball sprites
  SDL_Rect rcBounds = { 0, 0, 600, 400 };
  Sprite*  pSprite;
  pSprite = new Sprite(_pGolfBallImage, rcBounds, BA_WRAP);
  pSprite->SetVelocity(5, 3);
  pGE->AddSprite(pSprite);
  pSprite = new Sprite(_pGolfBallImage, rcBounds, BA_WRAP);
  pSprite->SetVelocity(3, 2);
  pGE->AddSprite(pSprite);
  rcBounds.x = 265; rcBounds.w = 500; rcBounds.h = 335;
  pSprite = new Sprite(_pGolfBallImage, rcBounds, BA_BOUNCE);
  pSprite->SetVelocity(-6, 5);
  pGE->AddSprite(pSprite);
  rcBounds.w = 470;
  pSprite = new Sprite(_pGolfBallImage, rcBounds, BA_BOUNCE);
  pSprite->SetVelocity(7, -3);
  pGE->AddSprite(pSprite);

  // Set the initial drag info
  _pDragSprite = NULL;
}

void Game::End()
{
  // Cleanup the bitmaps
  delete _pForestImage;
  delete _pGolfBallImage;

  GameEngine *pGameEngine = GameEngine::GetEngine();
    
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

  // Draw the background forest
  _pForestImage->Draw(renderer, 0, 0);

  // Draw the sprites
  pGameEngine->DrawSprites();
  
  SDL_RenderPresent(renderer);
}

void Game::Cycle()
{
  GameEngine *pGameEngine = GameEngine::GetEngine();
  
  // Update the sprites
  pGameEngine->UpdateSprites();  
}

bool Game::HandleKeys(){
  SDL_PumpEvents();
  const Uint8 *state = SDL_GetKeyboardState(NULL);

  //Q
  if (state[SDL_GetScancodeFromKey(SDLK_q)]) {
    return true;
  }

  return false;
}

void Game::MouseButtonDown(int x, int y, bool bLeft)
{
  GameEngine *pGameEngine = GameEngine::GetEngine();
  
  // See if a ball was clicked with the left mouse button
  if (bLeft && (_pDragSprite == NULL))
  {
    if ((_pDragSprite = pGameEngine->IsPointInSprite(x, y)) != NULL)
    {
      // Simulate a mouse move to get started
      MouseMove(x, y);
    }
  }
}

void Game::MouseButtonUp(int x, int y, bool bLeft)
{
  // Stop dragging
  _pDragSprite = NULL;  
}

void Game::MouseMove(int x, int y)
{
    if (_pDragSprite != NULL)
  {
    // Move the sprite to the mouse cursor position
    _pDragSprite->SetPosition(x - (_pDragSprite->GetWidth() / 2),
      y - (_pDragSprite->GetHeight() / 2));
  }
}

void Game::HandleJoystick(JOYSTATE jsJoystickState)
{
}

bool Game::SpriteCollision(Sprite* pSpriteHitter, Sprite* pSpriteHittee){
  // Swap the sprite velocities so that they appear to bounce
  SDL_Point ptSwapVelocity = pSpriteHitter->GetVelocity();
  pSpriteHitter->SetVelocity(pSpriteHittee->GetVelocity());
  pSpriteHittee->SetVelocity(ptSwapVelocity);
  return true;
}

void Game::SpriteDying(Sprite* pSprite){
  
}

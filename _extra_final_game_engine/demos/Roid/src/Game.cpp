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

  // Initialize the joystick
  
  return true;
}

void Game::Start()
{
  // Seed the random number generator
  srand(time(NULL));

  GameEngine *pGE = GameEngine::GetEngine();
  SDL_Renderer *renderer = pGE->GetRenderer();

  // Create and load the asteroid saucer bitmap
  SDL_Color scTrans = {255, 0, 255, 255};
  _pAsteroidImage = new Image(renderer, "res/Asteroid.png", &scTrans);
  _pSaucerImage = new Image(renderer, "res/Saucer.png", &scTrans);

  // Create the starry background
  _pBackground = new StarryBackground(500, 400);

  // Create the asteroid sprites
  SDL_Rect    rcBounds = { 0, 0, 500, 400 };
  _pAsteroids[0] = new Sprite(_pAsteroidImage, rcBounds, BA_WRAP);
  _pAsteroids[0]->SetNumFrames(14);
  _pAsteroids[0]->SetFrameDelay(1);
  _pAsteroids[0]->SetPosition(250, 200);
  _pAsteroids[0]->SetVelocity(-3, 1);
  pGE->AddSprite(_pAsteroids[0]);
  _pAsteroids[1] = new Sprite(_pAsteroidImage, rcBounds, BA_WRAP);
  _pAsteroids[1]->SetNumFrames(14);
  _pAsteroids[1]->SetFrameDelay(2);
  _pAsteroids[1]->SetPosition(250, 200);
  _pAsteroids[1]->SetVelocity(3, -2);
  pGE->AddSprite(_pAsteroids[1]);
  _pAsteroids[2] = new Sprite(_pAsteroidImage, rcBounds, BA_WRAP);
  _pAsteroids[2]->SetNumFrames(14);
  _pAsteroids[2]->SetFrameDelay(3);
  _pAsteroids[2]->SetPosition(250, 200);
  _pAsteroids[2]->SetVelocity(-2, -4);
  pGE->AddSprite(_pAsteroids[2]);

  
  // Create the saucer sprite
  _pSaucer = new Sprite(_pSaucerImage, rcBounds, BA_WRAP);
  _pSaucer->SetPosition(0, 0);
  _pSaucer->SetVelocity(3, 1);
  pGE->AddSprite(_pSaucer);  
}

void Game::End()
{
  GameEngine *pGameEngine = GameEngine::GetEngine();

  // Cleanup the asteroid bitmap
  delete _pAsteroidImage;
  delete _pSaucerImage;

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

  // Update the saucer to help it dodge the asteroids
  UpdateSaucer();
  
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

bool Game::SpriteCollision(Sprite* pSpriteHitter, Sprite* pSpriteHittee){
  return false;
}

void Game::SpriteDying(Sprite* pSprite){

}

//-----------------------------------------------------------------
// Functions
//-----------------------------------------------------------------
void Game::UpdateSaucer()
{
  // Obtain the saucer's position
  SDL_Rect rcSaucer, rcRoid;
  rcSaucer = _pSaucer->GetPosition();

  // Find out which asteroid is closest to the saucer
  int iXCollision = 500, iYCollision = 400, iXYCollision = 900;
  for (int i = 0; i < 3; i++)
  {
    // Get the asteroid position
    rcRoid = _pAsteroids[i]->GetPosition();

    // Calculate the minimum XY collision distance
    int iXCollisionDist = (rcSaucer.x +
      (rcSaucer.w - rcSaucer.x) / 2) -
      (rcRoid.x +
      (rcRoid.w - rcRoid.x) / 2);
    int iYCollisionDist = (rcSaucer.y +
      (rcSaucer.h - rcSaucer.y) / 2) -
      (rcRoid.y +
      (rcRoid.h - rcRoid.y) / 2);
    if ((abs(iXCollisionDist) < abs(iXCollision)) ||
      (abs(iYCollisionDist) < abs(iYCollision)))
      if ((abs(iXCollisionDist) + abs(iYCollisionDist)) < iXYCollision)
      {
        iXYCollision = abs(iXCollision) + abs(iYCollision);
        iXCollision = iXCollisionDist;
        iYCollision = iYCollisionDist;
      }
  }

  // Move to dodge the asteroids, if necessary
  SDL_Point ptVelocity;
  ptVelocity = _pSaucer->GetVelocity();
  if (abs(iXCollision) < 60)
  {
    // Adjust the X velocity
    if (iXCollision < 0)
      ptVelocity.x = max(ptVelocity.x - 1, -8);
    else
      ptVelocity.x = min(ptVelocity.x + 1, 8);
  }
  if (abs(iYCollision) < 60)
  {
    // Adjust the Y velocity
    if (iYCollision < 0)
      ptVelocity.y = max(ptVelocity.y - 1, -8);
    else
      ptVelocity.y = min(ptVelocity.y + 1, 8);
  }

  // Update the saucer to the new position
  _pSaucer->SetVelocity(ptVelocity);
}

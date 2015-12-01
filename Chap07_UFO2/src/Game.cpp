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
  pGameEngine->InitJoystick();
    
  return true;
}

void Game::Start()
{
  // Seed the random number generator
  srand(SDL_GetTicks());

  GameEngine *pGE = GameEngine::GetEngine();
  SDL_Renderer *renderer = pGE->GetRenderer();

  // Create and load the background and saucer bitmaps
  _pBackground = new Bitmap(renderer, "res/Background.bmp");

  SDL_Color scTransColor = {0xFF, 0x0, 0xFF, 0xFF};
  _pSaucer[0] = new Bitmap(renderer, "res/Saucer.bmp", &scTransColor);
  _pSaucer[1] = new Bitmap(renderer, "res/SaucerFlame.bmp", &scTransColor);

  // Set the initial saucer position and speed
  _iSaucerX = 250 - (_pSaucer[0]->GetWidth() / 2);
  _iSaucerY = 200 - (_pSaucer[0]->GetHeight() / 2);
  _iSpeedX = 0;
  _iSpeedY = 0;  
}

void Game::End()
{
  // Cleanup the background and saucer bitmaps
  delete _pBackground;
  delete _pSaucer[0];
  delete _pSaucer[1];
  
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

  // Draw the background and saucer bitmaps
  _pBackground->Draw(renderer, 0, 0);
  _pSaucer[_bSaucerFlame ? 1:0]->Draw(renderer, _iSaucerX, _iSaucerY);

  // Force a repaint to redraw the saucer
  SDL_RenderPresent(renderer);
}

void Game::Cycle()
{
  // Update the saucer position
  _iSaucerX = std::min(500 - _pSaucer[0]->GetWidth(),
		       std::max(0, _iSaucerX + _iSpeedX));
  
  _iSaucerY = std::min(320,
		       std::max(0, _iSaucerY + _iSpeedY));  
}

void Game::HandleKeys(){
  SDL_PumpEvents();
  const Uint8 *state = SDL_GetKeyboardState(NULL);

  //Q
  if (state[SDL_GetScancodeFromKey(SDLK_q)]) {
    exit(0);
  }

  //UP
  if (state[SDL_SCANCODE_UP]){
    _iSpeedY--;
    _iSpeedY = std::max(-_iMAXSPEED, _iSpeedY);

#ifdef DEBUG
    std::cout << "up key down. Y Speed is " << _iSpeedY << std::endl;
#endif    
  }

  //RIGHT
  if (state[SDL_SCANCODE_RIGHT]){
    _iSpeedX++;
    _iSpeedX = std::min(_iMAXSPEED, _iSpeedX);

#ifdef DEBUG
    std::cout << "right key down. X Speed is " << _iSpeedX << std::endl;
#endif    
  }

  //DOWN
  if (state[SDL_SCANCODE_DOWN]){
    _iSpeedY++;
    _iSpeedY = std::min(_iMAXSPEED, _iSpeedY);

#ifdef DEBUG
    std::cout << "down key down. Y Speed is " << _iSpeedY << std::endl;
#endif    
  }

  //LEFT
  if (state[SDL_SCANCODE_LEFT]){
    _iSpeedX--;
    _iSpeedX = std::max(-_iMAXSPEED, _iSpeedX);

#ifdef DEBUG
    std::cout << "left key down. X Speed is " << _iSpeedX << std::endl;
#endif    
  }
}

void Game::MouseButtonDown(int x, int y, bool bLeft)
{
  if (bLeft)
    {
      // Set the saucer position to the mouse position
      _iSaucerX = x - (_pSaucer[0]->GetWidth() / 2);
      _iSaucerY = y - (_pSaucer[0]->GetHeight() / 2);
    }
  else
    {
      // Stop the saucer
      _iSpeedX = 0;
      _iSpeedY = 0;
    }
}

void Game::MouseButtonUp(int x, int y, bool bLeft)
{
}

void Game::MouseMove(int x, int y)
{
}

void Game::HandleJoystick(JOYSTATE jsJoystickState)
{
  // Check horizontal movement
  if (jsJoystickState & JOY_LEFT)
    _iSpeedX = max(-_iMAXSPEED, _iSpeedX - 2);
  else if (jsJoystickState & JOY_RIGHT)
    _iSpeedX = min(_iMAXSPEED, _iSpeedX + 2);

  // Check vertical movement
  if (jsJoystickState & JOY_UP)
    _iSpeedY = max(-_iMAXSPEED, _iSpeedY - 2);
  else if (jsJoystickState & JOY_DOWN)
    _iSpeedY = min(_iMAXSPEED, _iSpeedY + 2);

  // Check primary joystick button
  _bSaucerFlame = (jsJoystickState & JOY_FIRE1);

  // Check secondary joystick button
  if (jsJoystickState & JOY_FIRE2)
  {
    // Force the flying saucer into hyperspace
    _iSaucerX = rand() % (500 - _pSaucer[0]->GetWidth());
    _iSaucerY = rand() % 320;
  }
}

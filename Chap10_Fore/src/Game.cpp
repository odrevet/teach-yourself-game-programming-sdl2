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
  _pForestBitmap = new Bitmap(renderer, "res/Forest.bmp");
  SDL_Color scTransColor = {0xFF, 0x0, 0xFF, 0xFF};
  _pGolfBallBitmap = new Bitmap(renderer, "res/GolfBall.bmp", &scTransColor);

  // Create the golf ball sprites
  SDL_Rect rcBounds = { 0, 0, 600, 400 };
  _pGolfBallSprite[0] = new Sprite(_pGolfBallBitmap, rcBounds);
  _pGolfBallSprite[1] = new Sprite(_pGolfBallBitmap, rcBounds, BA_WRAP);
  _pGolfBallSprite[2] = new Sprite(_pGolfBallBitmap, rcBounds, BA_BOUNCE);
  _pGolfBallSprite[0]->SetVelocity(2, 1);
  _pGolfBallSprite[1]->SetVelocity(3, -2);
  _pGolfBallSprite[2]->SetVelocity(7, 4);

  // Set the initial drag info
  _bDragging = false;
  _iDragBall = -1;

}

void Game::End()
{
  // Cleanup the bitmaps
  delete _pForestBitmap;
  delete _pGolfBallBitmap;

  // Cleanup the sprites
  for (int i = 0; i < 3; i++)
    delete _pGolfBallSprite[i];

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
  GameEngine *pGameEngine = GameEngine::GetEngine();
  SDL_Renderer *renderer = pGameEngine->GetRenderer();

  // Draw the background forest
  _pForestBitmap->Draw(renderer, 0, 0);

  // Draw the golf ball sprites
  for (int i = 0; i < 3; i++)
    _pGolfBallSprite[i]->Draw(renderer);
  
  SDL_RenderPresent(renderer);
}

void Game::Cycle()
{
  // Update the golf ball sprites
  for (int i = 0; i < 3; i++)
    _pGolfBallSprite[i]->Update();

}

void Game::HandleKeys(){
  SDL_PumpEvents();
  const Uint8 *state = SDL_GetKeyboardState(NULL);

  //Q
  if (state[SDL_GetScancodeFromKey(SDLK_q)]) {
    exit(0);
  }
}

void Game::MouseButtonDown(int x, int y, bool bLeft)
{
  // See if a ball was clicked with the left mouse button
  if (bLeft && !_bDragging)
  {
    for (int i = 0; i < 3; i++)
      if (_pGolfBallSprite[i]->IsPointInside(x, y))
      {
        // Set the drag state and the drag ball
        _bDragging = true;
        _iDragBall = i;
#ifdef DEBUG
	printf("dragging ball %d\n", i);
#endif
	
        // Simulate a mouse move to get started
        MouseMove(x, y);

        // Don't check for more balls
        break;
      }
  }
}

void Game::MouseButtonUp(int x, int y, bool bLeft)
{
  // Stop dragging
  _bDragging = false;
#ifdef DEBUG
  std::cout << "stoped dragging" << std::endl;
#endif
}

void Game::MouseMove(int x, int y)
{
  if (_bDragging)
  {
#ifdef DEBUG
    printf("moving ball %d to %d %d\n",
	   _iDragBall,
	   x - (_pGolfBallBitmap->GetWidth() / 2),
	   y - (_pGolfBallBitmap->GetHeight() / 2));
#endif    
    // Move the sprite to the mouse cursor position
    _pGolfBallSprite[_iDragBall]->SetPosition(
      x - (_pGolfBallBitmap->GetWidth() / 2),
      y - (_pGolfBallBitmap->GetHeight() / 2));
  }
}

void Game::HandleJoystick(JOYSTATE jsJoystickState)
{
}

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
  srand(time(NULL));

  GameEngine *pGE = GameEngine::GetEngine();
  SDL_Renderer *renderer = pGE->GetRenderer();

  // Create and load the bitmaps
  SDL_Color scTrans = {255, 0, 255, 255};
  _pHighwayBitmap = new Bitmap(renderer, "res/Highway.bmp");
  _pChickenBitmap = new Bitmap(renderer, "res/Chicken.bmp", &scTrans);
  _pCarBitmaps[0] = new Bitmap(renderer, "res/Car1.bmp", &scTrans);
  _pCarBitmaps[1] = new Bitmap(renderer, "res/Car2.bmp", &scTrans);
  _pCarBitmaps[2] = new Bitmap(renderer, "res/Car3.bmp", &scTrans);
  _pCarBitmaps[3] = new Bitmap(renderer, "res/Car4.bmp", &scTrans);
  _pChickenHeadBitmap = new Bitmap(renderer, "res/ChickenHead.bmp", &scTrans);


  // Create the chicken and car sprites
  Sprite* pSprite;
  SDL_Rect    rcBounds = { 0, 0, 465, 400 };
  _pChickenSprite = new Sprite(_pChickenBitmap, rcBounds, BA_STOP);
  _pChickenSprite->SetPosition(4, 175);
  _pChickenSprite->SetVelocity(0, 0);
  _pChickenSprite->SetZOrder(1);
  pGE->AddSprite(_pChickenSprite);
  pSprite = new Sprite(_pCarBitmaps[0], rcBounds, BA_WRAP);
  pSprite->SetPosition(70, 0);
  pSprite->SetVelocity(0, 7);
  pSprite->SetZOrder(2);
  pGE->AddSprite(pSprite);
  pSprite = new Sprite(_pCarBitmaps[1], rcBounds, BA_WRAP);
  pSprite->SetPosition(160, 0);
  pSprite->SetVelocity(0, 3);
  pSprite->SetZOrder(2);
  pGE->AddSprite(pSprite);
  pSprite = new Sprite(_pCarBitmaps[2], rcBounds, BA_WRAP);
  pSprite->SetPosition(239, 400);
  pSprite->SetVelocity(0, -5);
  pSprite->SetZOrder(2);
  pGE->AddSprite(pSprite);
  pSprite = new Sprite(_pCarBitmaps[3], rcBounds, BA_WRAP);
  pSprite->SetPosition(329, 400);
  pSprite->SetVelocity(0, -10);
  pSprite->SetZOrder(2);
  pGE->AddSprite(pSprite);

  // Initialize the remaining global variables
  _iInputDelay = 0;
  _iNumLives = 3;
  _iScore = 0;
  _bGameOver = false;
}

void Game::End()
{
  GameEngine *pGameEngine = GameEngine::GetEngine();

  // Cleanup the sprites
  pGameEngine->CleanupSprites();

  // Cleanup the bitmaps
  delete _pHighwayBitmap;
  delete _pChickenBitmap;
  for (int i = 0; i < 4; i++)
    delete _pCarBitmaps[i];
  delete _pChickenHeadBitmap;

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

  // Draw the background highway
  _pHighwayBitmap->Draw(renderer, 0, 0);

  // Draw the sprites
  pGameEngine->DrawSprites();

  // Draw the number of remaining chicken lives
  for (int i = 0; i < _iNumLives; i++)
    _pChickenHeadBitmap->Draw(renderer,
			      406 + (_pChickenHeadBitmap->GetWidth() * i),
			      382);

  SDL_RenderPresent(renderer);
}

void Game::Cycle()
{
  if (!_bGameOver)
    {
      GameEngine *pGameEngine = GameEngine::GetEngine();

      // Update the sprites
      pGameEngine->UpdateSprites();
    }
}

void Game::HandleKeys(){
  SDL_PumpEvents();
  const Uint8 *state = SDL_GetKeyboardState(NULL);

  //Q
  if (state[SDL_GetScancodeFromKey(SDLK_q)]) {
    exit(0);
  }

  if (!_bGameOver && (++_iInputDelay > 2))
  {
    // Move the chicken based upon key presses
    if (state[SDL_SCANCODE_LEFT])
      MoveChicken(-20, 0);
    else if (state[SDL_SCANCODE_RIGHT])
      MoveChicken(20, 0);
    if (state[SDL_SCANCODE_UP])
      MoveChicken(0, -20);
    if (state[SDL_SCANCODE_DOWN])
      MoveChicken(0, 20);

    // Reset the input delay
    _iInputDelay = 0;
  }
}

void Game::MouseButtonDown(int x, int y, bool bLeft)
{
  // Start a new game, if necessary
  if (_bGameOver)
  {
    _iNumLives = 3;
    _iScore = 0;
    _bGameOver = false;
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
  if (!_bGameOver && (++_iInputDelay > 2))
  {
    // Check horizontal movement
    if (jsJoystickState & JOY_LEFT)
        MoveChicken(-20, 0);
    else if (jsJoystickState & JOY_RIGHT)
        MoveChicken(20, 0);

    // Check vertical movement
    if (jsJoystickState & JOY_UP)
        MoveChicken(0, -20);
    else if (jsJoystickState & JOY_DOWN)
        MoveChicken(0, 20);

    // Reset the input delay
    _iInputDelay = 0;
  }

  // Check the joystick button and start a new game, if necessary
  if (_bGameOver && (jsJoystickState & JOY_FIRE1))
  {
    _iNumLives = 3;
    _iScore = 0;
    _bGameOver = false;
  }
}

bool Game::SpriteCollision(Sprite* pSpriteHitter, Sprite* pSpriteHittee){
  GameEngine *pGameEngine = GameEngine::GetEngine();

  // See if the chicken was hit
  if (pSpriteHittee == _pChickenSprite)
  {
    // Move the chicken back to the start
    _pChickenSprite->SetPosition(4, 175);

    // See if the game is over
    if (--_iNumLives > 0)
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION ,
			       "Henway",
			       "Ouch!",
			       pGameEngine->GetWindow());
    else
    {
      // Display game over message
      char szText[64];
      sprintf(szText, "Game Over! You scored %d points.", _iScore);
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION ,
			       "Henway",
			       szText,
			       pGameEngine->GetWindow());
      _bGameOver = true;
    }

    return false;
  }

  return true;
}


//-----------------------------------------------------------------
// Functions
//-----------------------------------------------------------------
void Game::MoveChicken(int iXDistance, int iYDistance)
{
  GameEngine *pGameEngine = GameEngine::GetEngine();
  
  // Move the chicken to its new position
  _pChickenSprite->OffsetPosition(iXDistance, iYDistance);

  // See if the chicken made it across
  if (_pChickenSprite->GetPosition().x > 400)
  {
    // Move the chicken back to the start and add to the score
    _pChickenSprite->SetPosition(4, 175);
    _iScore += 150;
     SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION ,
			       "Henway",
			       "You made it!",
			       pGameEngine->GetWindow());    
  }
}

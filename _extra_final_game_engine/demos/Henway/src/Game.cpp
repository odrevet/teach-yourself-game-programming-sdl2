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
  _pHighwayImage = new Image(renderer, "res/Highway.png");
  _pChickenImage = new Image(renderer, "res/Chicken.png", &scTrans);
  _pCarImages[0] = new Image(renderer, "res/Car1.png", &scTrans);
  _pCarImages[1] = new Image(renderer, "res/Car2.png", &scTrans);
  _pCarImages[2] = new Image(renderer, "res/Car3.png", &scTrans);
  _pCarImages[3] = new Image(renderer, "res/Car4.png", &scTrans);
  _pChickenHeadImage = new Image(renderer, "res/ChickenHead.png", &scTrans);

  // Create the chicken and car sprites
  Sprite *pSprite;
  SDL_Rect rcBounds = {0, 0, 465, 400};
  _pChickenSprite = new Sprite(_pChickenImage, rcBounds, BA_STOP);
  _pChickenSprite->SetPosition(4, 175);
  _pChickenSprite->SetVelocity(0, 0);
  _pChickenSprite->SetZOrder(1);
  pGE->AddSprite(_pChickenSprite);
  pSprite = new Sprite(_pCarImages[0], rcBounds, BA_WRAP);
  pSprite->SetPosition(70, 0);
  pSprite->SetVelocity(0, 7);
  pSprite->SetZOrder(2);
  pGE->AddSprite(pSprite);
  pSprite = new Sprite(_pCarImages[1], rcBounds, BA_WRAP);
  pSprite->SetPosition(160, 0);
  pSprite->SetVelocity(0, 3);
  pSprite->SetZOrder(2);
  pGE->AddSprite(pSprite);
  pSprite = new Sprite(_pCarImages[2], rcBounds, BA_WRAP);
  pSprite->SetPosition(239, 400);
  pSprite->SetVelocity(0, -5);
  pSprite->SetZOrder(2);
  pGE->AddSprite(pSprite);
  pSprite = new Sprite(_pCarImages[3], rcBounds, BA_WRAP);
  pSprite->SetPosition(329, 400);
  pSprite->SetVelocity(0, -10);
  pSprite->SetZOrder(2);
  pGE->AddSprite(pSprite);

  // Initialize the remaining global variables
  _iInputDelay = 0;
  _iNumLives = 3;
  _iScore = 0;
  _bGameOver = false;

  // Load the music
  _mmMusic = Mix_LoadMUS("res/Music.xm");
  if (_mmMusic == nullptr)
    cout << "Could not Music\n"
         << Mix_GetError();

  // Load the sound effects
  Mix_Chunk *_mcBoc = Mix_LoadWAV("res/Boc.wav");
  if (_mcBoc == nullptr)
    cout << "Could not load WAV\n"
         << Mix_GetError();

  _mcCarHorn1 = Mix_LoadWAV("res/CarHorn1.wav");
  _mcCarHorn2 = Mix_LoadWAV("res/CarHorn2.wav");
  _mcCelebrate = Mix_LoadWAV("res/Celebrate.wav");
  _mcGameOver = Mix_LoadWAV("res/GameOver.wav");
  _mcSquish = Mix_LoadWAV("res/Squish.wav");

  // Play the background music
  pGE->PlaySong(_mmMusic);
}

void Game::End()
{
  GameEngine *pGameEngine = GameEngine::GetEngine();

  // Cleanup the sprites
  pGameEngine->CleanupSprites();

  // Cleanup the music
  Mix_FreeMusic(_mmMusic);

  // Cleanup the sound effetcs
  Mix_FreeChunk(_mcCarHorn1);
  Mix_FreeChunk(_mcCarHorn2);
  Mix_FreeChunk(_mcGameOver);
  Mix_FreeChunk(_mcSquish);

  // Cleanup the bitmaps
  delete _pHighwayImage;
  delete _pChickenImage;
  for (int i = 0; i < 4; i++)
    delete _pCarImages[i];
  delete _pChickenHeadImage;

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
  _pHighwayImage->Draw(renderer, 0, 0);

  // Draw the sprites
  pGameEngine->DrawSprites();

  // Draw the number of remaining chicken lives
  for (int i = 0; i < _iNumLives; i++)
    _pChickenHeadImage->Draw(renderer,
                             406 + (_pChickenHeadImage->GetWidth() * i),
                             382);

  SDL_RenderPresent(renderer);
}

void Game::Cycle()
{
  if (!_bGameOver)
  {
    GameEngine *pGameEngine = GameEngine::GetEngine();

    // Play a random car sound randomly
    if (rand() % 100 == 0)
    {
      if (rand() % 2 == 0)
        Mix_PlayChannel(-1, _mcCarHorn1, 0);
      else
        Mix_PlayChannel(-1, _mcCarHorn2, 0);
    }

    // Update the sprites
    pGameEngine->UpdateSprites();
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

  return false;
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

bool Game::SpriteCollision(Sprite *pSpriteHitter, Sprite *pSpriteHittee)
{
  GameEngine *pGameEngine = GameEngine::GetEngine();

  // See if the chicken was hit
  if (pSpriteHittee == _pChickenSprite)
  {
    // Move the chicken back to the start
    _pChickenSprite->SetPosition(4, 175);

    // See if the game is over
    if (--_iNumLives > 0)
      // Play a sound for the chicken getting hit
      Mix_PlayChannel(-1, _mcSquish, 0);
    else
    {
      // Play a sound for the game ending
      Mix_PlayChannel(-1, _mcGameOver, 0);

      // Display game over message
      char szText[64];
      sprintf(szText, "Game Over! You scored %d points.", _iScore);
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
                               "Henway",
                               szText,
                               pGameEngine->GetWindow());
      _bGameOver = true;

      // Pause the background music
      pGameEngine->PauseSong();
    }

    return false;
  }

  return true;
}

void Game::SpriteDying(Sprite *pSprite)
{
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
    // Play a sound for the chicken making it safely across
    Mix_PlayChannel(-1, _mcCelebrate, 0);

    // Move the chicken back to the start and add to the score
    _pChickenSprite->SetPosition(4, 175);
    _iScore += 150;
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
                             "Henway",
                             "You made it!",
                             pGameEngine->GetWindow());
  }
}

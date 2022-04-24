//-----------------------------------------------------------------
// Game Skeleton Application
// C++ Source - Skeleton.cpp
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Game.h"

int Game::_iDifficulty = 0;
Image *Game::_pBlobboImage = nullptr;
Image *Game::_pBMissileImage = nullptr;
Image *Game::_pJellyImage = nullptr;
Image *Game::_pJMissileImage = nullptr;
Image *Game::_pTimmyImage = nullptr;
Image *Game::_pTMissileImage = nullptr;

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

  // init text
  _ttfFont = TTF_OpenFont("res/DejaVuSans.ttf", 12);
  if (_ttfFont == nullptr)
  {
    std::cout << " Failed to load font : " << TTF_GetError() << std::endl;
    return false;
  }

  return true;
}

void Game::Start()
{
  // Read the hi scores
  ReadHiScores();

  // Seed the random number generator
  srand(time(NULL));

  GameEngine *pGE = GameEngine::GetEngine();
  SDL_Renderer *renderer = pGE->GetRenderer();

  // Create and load the bitmaps
  SDL_Color scTrans = {255, 0, 255, 255};
  _pDesertImage = new Image(renderer, "res/Desert.png", &scTrans);
  _pCarImage = new Image(renderer, "res/Car.png", &scTrans);
  _pSmCarImage = new Image(renderer, "res/SmCar.png", &scTrans);
  _pMissileImage = new Image(renderer, "res/Missile.png", &scTrans);
  Game::_pBlobboImage = new Image(renderer, "res/Blobbo.png", &scTrans);
  Game::_pBMissileImage = new Image(renderer, "res/BMissile.png", &scTrans);
  Game::_pJellyImage = new Image(renderer, "res/Jelly.png", &scTrans);
  Game::_pJMissileImage = new Image(renderer, "res/JMissile.png", &scTrans);
  Game::_pTimmyImage = new Image(renderer, "res/Timmy.png", &scTrans);
  Game::_pTMissileImage = new Image(renderer, "res/TMissile.png", &scTrans);
  _pSmExplosionImage = new Image(renderer, "res/SmExplosion.png", &scTrans);
  _pLgExplosionImage = new Image(renderer, "res/LgExplosion.png", &scTrans);
  _pGameOverImage = new Image(renderer, "res/GameOver.png", &scTrans);
  _pSplashImage = new Image(renderer, "res/Splash.png", &scTrans);

  // Create the starry background
  _pBackground = new StarryBackground(600, 450);

  // Load sound effects
  _mcMissile = Mix_LoadWAV("res/Missile.wav");
  _mcJMissile = Mix_LoadWAV("res/JMissile.wav");
  _mcBMissile = Mix_LoadWAV("res/BMissile.wav");
  _mcTMissile = Mix_LoadWAV("res/TMissile.wav");
  _mcSmExplode = Mix_LoadWAV("res/SmExplode.wav");
  _mcLgExplode = Mix_LoadWAV("res/LgExplode.wav");
  _mcGameOver = Mix_LoadWAV("res/GameOver.wav");

  // Load music
  _mmMusic = Mix_LoadMUS("res/Music.xm");

  // Set the splash screen variable
  _bDemo = true;
  NewGame();
}

void Game::End()
{
  GameEngine *pGameEngine = GameEngine::GetEngine();

  // Cleanup the bitmaps
  delete _pDesertImage;
  delete _pCarImage;
  delete _pSmCarImage;
  delete _pMissileImage;
  delete _pBlobboImage;
  delete _pBMissileImage;
  delete _pJellyImage;
  delete _pJMissileImage;
  delete _pTimmyImage;
  delete _pTMissileImage;
  delete _pSmExplosionImage;
  delete _pLgExplosionImage;
  delete _pGameOverImage;
  delete _pSplashImage;

  // Cleanup the background
  delete _pBackground;

  // Cleanup the sprites
  pGameEngine->CleanupSprites();

  // Cleanup the sound effects
  Mix_FreeChunk(_mcMissile);
  Mix_FreeChunk(_mcJMissile);
  Mix_FreeChunk(_mcBMissile);
  Mix_FreeChunk(_mcTMissile);
  Mix_FreeChunk(_mcSmExplode);
  Mix_FreeChunk(_mcLgExplode);
  Mix_FreeChunk(_mcGameOver);

  // Cleanup the music
  Mix_FreeMusic(_mmMusic);

  // Cleanup the game engine
  delete pGameEngine;

  // Save the hi scores
  WriteHiScores();
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

  // Draw the desert bitmap
  _pDesertImage->Draw(renderer, 0, 371);

  // Draw the sprites
  pGameEngine->DrawSprites();

  if (_bDemo)
  {
    // Draw the splash screen image
    _pSplashImage->Draw(renderer, 142, 100);

    // Draw the hi scores
    char szText[64];
    SDL_Rect rect = {275, 320, 15, 15};
    sprintf(szText, "%d", _iScore);
    SDL_Color text_color = {255, 255, 255, 255};

    for (int i = 0; i < 5; i++)
    {
      sprintf(szText, "%d", _iHiScores[i]);
      SDL_Texture *text_texture = pGameEngine->DrawText(renderer,
                                                        szText,
                                                        _ttfFont,
                                                        text_color);
      SDL_QueryTexture(text_texture, NULL, NULL, &rect.w, &rect.h);
      if (text_texture)
        SDL_RenderCopy(renderer, text_texture, NULL, &rect);
      rect.y += 20;
    }
  }
  else
  {
    // Draw the score
    char szText[64];
    SDL_Rect rect = {460, 0, 15, 15};
    sprintf(szText, "%d", _iScore);
    SDL_Color text_color = {255, 255, 255, 255};
    SDL_Texture *text_texture = pGameEngine->DrawText(renderer,
                                                      szText,
                                                      _ttfFont,
                                                      text_color);
    SDL_QueryTexture(text_texture, NULL, NULL, &rect.w, &rect.h);
    if (text_texture)
      SDL_RenderCopy(renderer, text_texture, NULL, &rect);

    // Draw the number of remaining lives (cars)
    for (int i = 0; i < _iNumLives; i++)
      _pSmCarImage->Draw(renderer,
                         520 + (_pSmCarImage->GetWidth() * i),
                         10);

    // Draw the number of remaining lives (cars)
    for (int i = 0; i < _iNumLives; i++)
      _pSmCarImage->Draw(renderer,
                         520 + (_pSmCarImage->GetWidth() * i),
                         10);

    // Draw the game over message, if necessary
    if (_bGameOver)
      _pGameOverImage->Draw(renderer, 190, 149);
  }
  SDL_RenderPresent(renderer);
}

void Game::Cycle()
{
  GameEngine *pGameEngine = GameEngine::GetEngine();

  if (!_bGameOver)
  {
    if (!_bDemo)
    {
      // Randomly add aliens
      if ((rand() % Game::_iDifficulty) == 0)
        AddAlien();
    }
    // Update the background
    _pBackground->Update();

    // Update the sprites
    pGameEngine->UpdateSprites();
  }
  else if (--_iGameOverDelay == 0)
  {
    // Stop the music and switch to demo mode
    pGameEngine->PauseSong();
    _bDemo = true;
    NewGame();
  }
}

bool Game::HandleKeys()
{
  GameEngine *pGameEngine = GameEngine::GetEngine();

  SDL_PumpEvents();
  const Uint8 *state = SDL_GetKeyboardState(NULL);

  // Q
  if (state[SDL_GetScancodeFromKey(SDLK_q)])
  {
    return true;
  }

  if (!_bGameOver && !_bDemo)
  {
    // Move the car based upon left/right key presses
    SDL_Point ptVelocity = _pCarSprite->GetVelocity();
    if (state[SDL_SCANCODE_LEFT])
    {
      // Move left
      ptVelocity.x = max(ptVelocity.x - 1, -4);
      _pCarSprite->SetVelocity(ptVelocity);
    }
    else if (state[SDL_SCANCODE_RIGHT])
    {
      // Move right
      ptVelocity.x = min(ptVelocity.x + 2, 6);
      _pCarSprite->SetVelocity(ptVelocity);
    }

    // Fire missiles based upon spacebar presses
    if ((++_iFireInputDelay > 6) && state[SDL_SCANCODE_SPACE])
    {
      // Create a new missile sprite
      SDL_Rect rcBounds = {0, 0, 600, 450};
      SDL_Rect rcPos = _pCarSprite->GetPosition();
      Sprite *pSprite = new Sprite(_pMissileImage, rcBounds, BA_DIE);
      pSprite->SetPosition(rcPos.x + 15, 400);
      pSprite->SetVelocity(0, -7);
      pGameEngine->AddSprite(pSprite);

      // Play the missile (fire) sound
      Mix_PlayChannel(-1, _mcMissile, 0);

      // Reset the input delay
      _iFireInputDelay = 0;
    }
  }

  // Start a new game based upon an Enter (Return) key press
  if (state[SDL_SCANCODE_RETURN])
  {
    if (_bDemo)
    {
      // Start a new game without the splash screen
      _bDemo = false;
      NewGame();
    }
    else if (_bGameOver)
    {
      // Start a new game
      NewGame();
    }
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

bool Game::SpriteCollision(Sprite *pSpriteHitter, Sprite *pSpriteHittee)
{
  GameEngine *pGameEngine = GameEngine::GetEngine();

  // See if a player missile and an alien have collided
  Image *pHitter = pSpriteHitter->GetImage();
  Image *pHittee = pSpriteHittee->GetImage();
  if ((pHitter == _pMissileImage && (pHittee == _pBlobboImage ||
                                     pHittee == _pJellyImage || pHittee == _pTimmyImage)) ||
      (pHittee == _pMissileImage && (pHitter == _pBlobboImage ||
                                     pHitter == _pJellyImage || pHitter == _pTimmyImage)))
  {
    // Play the small explosion sound
    Mix_PlayChannel(-1, _mcSmExplode, 0);

    // Kill both sprites
    pSpriteHitter->Kill();
    pSpriteHittee->Kill();

    // Create a large explosion sprite at the alien's position
    SDL_Rect rcBounds = {0, 0, 600, 450};
    SDL_Rect rcPos;
    if (pHitter == _pMissileImage)
      rcPos = pSpriteHittee->GetPosition();
    else
      rcPos = pSpriteHitter->GetPosition();
    Sprite *pSprite = new Sprite(_pLgExplosionImage, rcBounds);
    pSprite->SetNumFrames(8, true);
    pSprite->SetPosition(rcPos.x, rcPos.y);
    pGameEngine->AddSprite(pSprite);

    // Update the score
    _iScore += 25;
    _iDifficulty = max(80 - (_iScore / 20), 20);
  }

  // See if an alien missile has collided with the car
  if ((pHitter == _pCarImage && (pHittee == _pBMissileImage ||
                                 pHittee == _pJMissileImage || pHittee == _pTMissileImage)) ||
      (pHittee == _pCarImage && (pHitter == _pBMissileImage ||
                                 pHitter == _pJMissileImage || pHitter == _pTMissileImage)))
  {
    // Play the large explosion sound
    Mix_PlayChannel(-1, _mcLgExplode, 0);

    // Kill the missile sprite
    if (pHitter == _pCarImage)
      pSpriteHittee->Kill();
    else
      pSpriteHitter->Kill();

    // Create a large explosion sprite at the car's position
    SDL_Rect rcBounds = {0, 0, 600, 480};
    SDL_Rect rcPos;
    if (pHitter == _pCarImage)
      rcPos = pSpriteHitter->GetPosition();
    else
      rcPos = pSpriteHittee->GetPosition();
    Sprite *pSprite = new Sprite(_pLgExplosionImage, rcBounds);
    pSprite->SetNumFrames(8, true);
    pSprite->SetPosition(rcPos.x, rcPos.y);
    pGameEngine->AddSprite(pSprite);

    // Move the car back to the start
    _pCarSprite->SetPosition(300, 405);

    // See if the game is over
    if (--_iNumLives == 0)
    {
      // Play the game over sound
      Mix_PlayChannel(-1, _mcGameOver, 0);
      _bGameOver = true;
      _iGameOverDelay = 150;

      // Update the hi scores
      UpdateHiScores();
    }
  }

  return false;
}

void Game::SpriteDying(Sprite *pSprite)
{
  // See if an alien missile sprite is dying
  if (pSprite->GetImage() == _pBMissileImage ||
      pSprite->GetImage() == _pJMissileImage ||
      pSprite->GetImage() == _pTMissileImage)
  {
    // Play the small explosion sound
    Mix_PlayChannel(-1, _mcSmExplode, 0);

    // Create a small explosion sprite at the missile's position
    SDL_Rect rcBounds = {0, 0, 600, 450};
    SDL_Rect rcPos = pSprite->GetPosition();
    Sprite *pSprite = new Sprite(_pSmExplosionImage, rcBounds);
    pSprite->SetNumFrames(8, true);
    pSprite->SetPosition(rcPos.x, rcPos.y);
    GameEngine *pGameEngine = GameEngine::GetEngine();
    pGameEngine->AddSprite(pSprite);
  }
}

//-----------------------------------------------------------------
// Functions
//-----------------------------------------------------------------
void Game::NewGame()
{
  GameEngine *pGameEngine = GameEngine::GetEngine();

  // Clear the sprites
  pGameEngine->CleanupSprites();

  // Initialize the game variables
  _iFireInputDelay = 0;
  _iScore = 0;
  _iNumLives = 3;
  Game::_iDifficulty = 80;
  _bGameOver = false;

  if (_bDemo)
  {
    // Add a few aliens to the demo
    for (int i = 0; i < 6; i++)
      AddAlien();
  }
  else
  {
    // Create the car sprite
    SDL_Rect rcBounds = {0, 0, 600, 450};
    _pCarSprite = new Sprite(_pCarImage, rcBounds, BA_WRAP);
    _pCarSprite->SetPosition(300, 405);
    pGameEngine->AddSprite(_pCarSprite);

    // Play the background music
    pGameEngine->PlaySong(_mmMusic);
  }
}

void Game::AddAlien()
{
  // Create a new random alien sprite
  SDL_Rect rcBounds = {0, 0, 600, 410};
  AlienSprite *pSprite;
  switch (rand() % 3)
  {
  case 0:
    // Blobbo
    pSprite = new AlienSprite(_pBlobboImage, rcBounds, BA_BOUNCE);
    pSprite->SetNumFrames(8);
    pSprite->SetPosition(((rand() % 2) == 0) ? 0 : 600, rand() % 370);
    pSprite->SetVelocity((rand() % 7) - 2, (rand() % 7) - 2);
    break;
  case 1:
    // Jelly
    pSprite = new AlienSprite(_pJellyImage, rcBounds, BA_BOUNCE);
    pSprite->SetNumFrames(8);
    pSprite->SetPosition(rand() % 600, rand() % 370);
    pSprite->SetVelocity((rand() % 5) - 2, (rand() % 5) + 3);
    break;
  case 2:
    // Timmy
    pSprite = new AlienSprite(_pTimmyImage, rcBounds, BA_WRAP);
    pSprite->SetNumFrames(8);
    pSprite->SetPosition(rand() % 600, rand() % 370);
    pSprite->SetVelocity((rand() % 7) + 3, 0);
    break;
  }

  // Add the alien sprite
  GameEngine *pGameEngine = GameEngine::GetEngine();
  pGameEngine->AddSprite(pSprite);
}

void Game::UpdateHiScores()
{
  // See if the current score made the hi score list
  int i;
  for (i = 0; i < 5; i++)
  {
    if (_iScore > _iHiScores[i])
      break;
  }

  // Insert the current score into the hi score list
  if (i < 5)
  {
    for (int j = 4; j > i; j--)
    {
      _iHiScores[j] = _iHiScores[j - 1];
    }
    _iHiScores[i] = _iScore;
  }
}

bool Game::ReadHiScores()
{
  SDL_RWops *hFile = SDL_RWFromFile("res/HiScores.dat", "r");

  if (hFile == NULL)
  {
    // The hi score file doesn't exist, so initialize the scores to 0
    for (int i = 0; i < 5; i++)
      _iHiScores[i] = 0;

#ifdef DEBUG
    cout << "Hi-Score initialized to 0" << endl;
#endif

    return false;
  }

  // Read the scores
  for (int i = 0; i < 5; i++)
  {
    // Read the score
    char cData[6];
    SDL_RWread(hFile, &cData, 1, 5);
#ifdef DEBUG
    cout << "Read hi score " << cData << endl;
#endif
    // Extract each integer score from the score data
    _iHiScores[i] = atoi(cData);
  }

  // Close the file
  return SDL_RWclose(hFile) == 0 ? true : false;
}

bool Game::WriteHiScores()
{
  SDL_RWops *hFile = SDL_RWFromFile("res/HiScores.dat", "w");

  if (hFile == NULL)
  {
#ifdef DEBUG
    cout << "Could not create HiScores.dat because " << SDL_GetError() << endl;
#endif

    // The hi score file couldn't be created, so bail
    return false;
  }

  // Write the scores
  for (int i = 0; i < 5; i++)
  {
    // Format each score for writing
    char cData[6];
    sprintf(cData, "%05d", _iHiScores[i]);
    SDL_RWwrite(hFile, &cData, 1, strlen(cData));
#ifdef DEBUG
    cout << "writed hi score " << cData << endl;
#endif
  }

  // Close the file
  return SDL_RWclose(hFile) == 0 ? true : false;
}

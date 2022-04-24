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

  // init text
  _ttfFont = TTF_OpenFont("res/DejaVuSans.ttf", 12);
  if (_ttfFont == nullptr)
  {
    std::cout << " Failed to load font : " << TTF_GetError() << std::endl;
    return false;
  }

  // Hide the mouse pointer
  SDL_ShowCursor(false);

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
  _pGroundBitmap = new Bitmap(renderer, "res/Ground.bmp", &scTrans);
  _pTargetBitmap = new Bitmap(renderer, "res/Target.bmp", &scTrans);
  _pCityBitmap = new Bitmap(renderer, "res/City.bmp", &scTrans);
  _pMeteorBitmap = new Bitmap(renderer, "res/Meteor.bmp", &scTrans);
  _pMissileBitmap = new Bitmap(renderer, "res/Missile.bmp", &scTrans);
  _pExplosionBitmap = new Bitmap(renderer, "res/Explosion.bmp", &scTrans);
  _pGameOverBitmap = new Bitmap(renderer, "res/GameOver.bmp", &scTrans);

  // Create the starry background
  _pBackground = new StarryBackground(600, 450);

  // Load the music
  _mmMusic = Mix_LoadMUS("res/Music.xm");
  if (_mmMusic == nullptr)
    cout << "Could not play music: " << Mix_GetError();

  // Load the sound effects
  _mcFire = Mix_LoadWAV("res/Fire.wav");
  _mcExplode = Mix_LoadWAV("res/Explode.wav");
  _mcBigExplode = Mix_LoadWAV("res/BigExplode.wav");

  // Start the game
  NewGame();
}

void Game::End()
{
  GameEngine *pGameEngine = GameEngine::GetEngine();

  // Cleanup the bitmaps
  delete _pGroundBitmap;
  delete _pTargetBitmap;
  delete _pCityBitmap;
  delete _pMeteorBitmap;
  delete _pMissileBitmap;
  delete _pExplosionBitmap;
  delete _pGameOverBitmap;

  // Cleanup the background
  delete _pBackground;

  // Cleanup the sprites
  pGameEngine->CleanupSprites();

  // cleanup the sound effects
  Mix_FreeChunk(_mcFire);
  Mix_FreeChunk(_mcExplode);
  Mix_FreeChunk(_mcBigExplode);

  // cleanup the music
  Mix_FreeMusic(_mmMusic);

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

  // Draw the ground bitmap
  _pGroundBitmap->Draw(renderer, 0, 398);

  // Draw the sprites
  pGameEngine->DrawSprites();

  // Draw the score
  char szText[64];
  SDL_Rect rect = {275, 0, 25, 25};
  sprintf(szText, "%d", _iScore);
  SDL_Color text_color = {255, 255, 255, 255};
  SDL_Texture *text_texture = pGameEngine->DrawText(renderer,
                                                    szText,
                                                    _ttfFont,
                                                    text_color);
  if (text_texture)
    SDL_RenderCopy(renderer, text_texture, NULL, &rect);

  // Draw the game over message, if necessary
  if (_bGameOver)
    _pGameOverBitmap->Draw(renderer, 170, 150);

  SDL_RenderPresent(renderer);
}

void Game::Cycle()
{
  if (!_bGameOver)
  {
    // Randomly add meteors
    if ((rand() % _iDifficulty) == 0)
      AddMeteor();

    GameEngine *pGameEngine = GameEngine::GetEngine();

    // Update the background
    _pBackground->Update();

    // Update the sprites
    pGameEngine->UpdateSprites();
  }
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
  if (!_bGameOver && bLeft)
  {
    // Create a new missile sprite and set its position
    SDL_Rect rcBounds = {0, 0, 600, 450};
    int iXPos = (x < 300) ? 144 : 449;
    Sprite *pSprite = new Sprite(_pMissileBitmap, rcBounds, BA_DIE);
    pSprite->SetPosition(iXPos, 365);

    // Calculate the velocity so that it is aimed at the target
    int iXVel, iYVel = -6;
    y = min(y, 300);
    iXVel = (iYVel * ((iXPos + 8) - x)) / (365 - y);
    pSprite->SetVelocity(iXVel, iYVel);

    GameEngine *pGameEngine = GameEngine::GetEngine();

    // Add the missile sprite
    pGameEngine->AddSprite(pSprite);

    // Play the fire sound
    Mix_PlayChannel(-1, _mcFire, 0);

    // Update the score
    _iScore--;
    _iScore = max(_iScore, 0);
  }
  else if (_bGameOver && !bLeft)
    // Start a new game
    NewGame();
}

void Game::MouseButtonUp(int x, int y, bool bLeft)
{
}

void Game::MouseMove(int x, int y)
{
  // Track the mouse with the target sprite
  _pTargetSprite->SetPosition(x - (_pTargetSprite->GetWidth() / 2),
                              y - (_pTargetSprite->GetHeight() / 2));
}

void Game::HandleJoystick(JOYSTATE jsJoystickState)
{
}

bool Game::SpriteCollision(Sprite *pSpriteHitter, Sprite *pSpriteHittee)
{
  // See if a missile and a meteor have collided
  if ((pSpriteHitter->GetBitmap() == _pMissileBitmap &&
       pSpriteHittee->GetBitmap() == _pMeteorBitmap) ||
      (pSpriteHitter->GetBitmap() == _pMeteorBitmap &&
       pSpriteHittee->GetBitmap() == _pMissileBitmap))
  {
    // Kill both sprites
    pSpriteHitter->Kill();
    pSpriteHittee->Kill();

    // Update the score
    _iScore += 6;
    _iDifficulty = max(50 - (_iScore / 10), 5);
  }

  // See if a meteor has collided with a city
  if (pSpriteHitter->GetBitmap() == _pMeteorBitmap &&
      pSpriteHittee->GetBitmap() == _pCityBitmap)
  {
    // Play the big explosion sound
    Mix_PlayChannel(-1, _mcBigExplode, 0);

    // Kill both sprites
    pSpriteHitter->Kill();
    pSpriteHittee->Kill();

    // See if the game is over
    if (--_iNumCities == 0)
      _bGameOver = true;
  }

  return false;
}

void Game::SpriteDying(Sprite *pSprite)
{
  // See if a meteor sprite is dying
  if (pSprite->GetBitmap() == _pMeteorBitmap)
  {
    GameEngine *pGameEngine = GameEngine::GetEngine();

    // Play the explosion sound
    Mix_PlayChannel(-1, _mcExplode, 0);

    // Create an explosion sprite at the meteor's position
    SDL_Rect rcBounds = {0, 0, 600, 450};
    SDL_Rect rcPos = pSprite->GetPosition();
    Sprite *pSprite = new Sprite(_pExplosionBitmap, rcBounds);
    pSprite->SetNumFrames(12, true);
    pSprite->SetPosition(rcPos.x, rcPos.y);
    pGameEngine->AddSprite(pSprite);
  }
}

void Game::NewGame()
{
  GameEngine *pGameEngine = GameEngine::GetEngine();

  // Clear the sprites
  pGameEngine->CleanupSprites();

  // Create the target sprite
  SDL_Rect rcBounds = {0, 0, 600, 450};
  _pTargetSprite = new Sprite(_pTargetBitmap, rcBounds, BA_STOP);
  _pTargetSprite->SetZOrder(10);
  pGameEngine->AddSprite(_pTargetSprite);

  // Create the city sprites
  Sprite *pSprite = new Sprite(_pCityBitmap, rcBounds);
  pSprite->SetPosition(2, 370);
  pGameEngine->AddSprite(pSprite);
  pSprite = new Sprite(_pCityBitmap, rcBounds);
  pSprite->SetPosition(186, 370);
  pGameEngine->AddSprite(pSprite);
  pSprite = new Sprite(_pCityBitmap, rcBounds);
  pSprite->SetPosition(302, 370);
  pGameEngine->AddSprite(pSprite);
  pSprite = new Sprite(_pCityBitmap, rcBounds);
  pSprite->SetPosition(490, 370);
  pGameEngine->AddSprite(pSprite);

  // Initialize the game variables
  _iScore = 0;
  _iNumCities = 4;
  _iDifficulty = 50;
  _bGameOver = false;

  // Play the background music
  pGameEngine->PlaySong(_mmMusic);
}

void Game::AddMeteor()
{
  GameEngine *pGameEngine = GameEngine::GetEngine();

  // Create a new meteor sprite and set its position
  SDL_Rect rcBounds = {0, 0, 600, 390};
  int iXPos = rand() % 600;
  Sprite *pSprite = new Sprite(_pMeteorBitmap, rcBounds, BA_DIE);
  pSprite->SetNumFrames(14);
  pSprite->SetPosition(iXPos, 0);

  // Calculate the velocity so that it is aimed at one of the cities
  int iXVel, iYVel = (rand() % 4) + 3;
  switch (rand() % 4)
  {
  case 0:
    iXVel = (iYVel * (56 - (iXPos + 50))) / 400;
    break;
  case 1:
    iXVel = (iYVel * (240 - (iXPos + 50))) / 400;
    break;
  case 2:
    iXVel = (iYVel * (360 - (iXPos + 50))) / 400;
    break;
  case 3:
    iXVel = (iYVel * (546 - (iXPos + 50))) / 400;
    break;
  }
  pSprite->SetVelocity(iXVel, iYVel);

  // Add the meteor sprite
  pGameEngine->AddSprite(pSprite);
}

//-----------------------------------------------------------------
// Game Skeleton Application
// C++ Source - Skeleton.cpp
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Game.h"


int Game::_iDifficulty = 0;
Bitmap* Game::_pBlobboBitmap = nullptr;
Bitmap* Game::_pBMissileBitmap = nullptr;
Bitmap* Game::_pJellyBitmap = nullptr;
Bitmap* Game::_pJMissileBitmap = nullptr;
Bitmap* Game::_pTimmyBitmap = nullptr;
Bitmap* Game::_pTMissileBitmap = nullptr;

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

  //init text
  _ttfFont = TTF_OpenFont("res/DejaVuSans.ttf", 12);
  if ( _ttfFont == nullptr ){
    std::cout << " Failed to load font : " << TTF_GetError() << std::endl;
    return false;
  }
  
  return true;
}

void Game::Start()
{
  // Seed the random number generator
  srand(time(NULL));

  GameEngine *pGE = GameEngine::GetEngine();
  SDL_Renderer *renderer = pGE->GetRenderer();
  SDL_Color scTrans = {255, 0, 255, 255};
  _pDesertBitmap = new Bitmap(renderer, "res/Desert.bmp", &scTrans);
  _pCarBitmap    = new Bitmap(renderer, "res/Car.bmp", &scTrans);
  _pSmCarBitmap  = new Bitmap(renderer, "res/SmCar.bmp", &scTrans);
  _pMissileBitmap = new Bitmap(renderer, "res/Missile.bmp", &scTrans);
  Game::_pBlobboBitmap   = new Bitmap(renderer, "res/Blobbo.bmp", &scTrans);
  Game::_pBMissileBitmap = new Bitmap(renderer, "res/BMissile.bmp", &scTrans);
  Game::_pJellyBitmap    = new Bitmap(renderer, "res/Jelly.bmp", &scTrans);
  Game::_pJMissileBitmap = new Bitmap(renderer, "res/JMissile.bmp", &scTrans);
  Game::_pTimmyBitmap    = new Bitmap(renderer, "res/Timmy.bmp", &scTrans);
  Game::_pTMissileBitmap = new Bitmap(renderer, "res/TMissile.bmp", &scTrans);
  _pSmExplosionBitmap = new Bitmap(renderer, "res/SmExplosion.bmp", &scTrans);
  _pLgExplosionBitmap = new Bitmap(renderer, "res/LgExplosion.bmp", &scTrans);
  _pGameOverBitmap    = new Bitmap(renderer, "res/GameOver.bmp", &scTrans);

  // Create the starry background
  _pBackground = new StarryBackground(600, 450);

  //Load sound effects
  _mcMissile = Mix_LoadWAV("res/Missile.wav");
  _mcJMissile = Mix_LoadWAV("res/JMissile.wav");
  _mcBMissile = Mix_LoadWAV("res/BMissile.wav");
  _mcTMissile = Mix_LoadWAV("res/TMissile.wav");
  _mcSmExplode = Mix_LoadWAV("res/SmExplode.wav");
  _mcLgExplode = Mix_LoadWAV("res/LgExplode.wav");
  _mcGameOver = Mix_LoadWAV("res/GameOver.wav");

  //Load music
  _mmMusic = Mix_LoadMUS("res/Music.xm");

  //Play music
  pGE->PlaySong(_mmMusic);
  
  // Start the game
  NewGame();  
}

void Game::End()
{
  GameEngine *pGameEngine = GameEngine::GetEngine();

  // Cleanup the bitmaps
  delete _pDesertBitmap;
  delete _pCarBitmap;
  delete _pSmCarBitmap;
  delete _pMissileBitmap;
  delete _pBlobboBitmap;
  delete _pBMissileBitmap;
  delete _pJellyBitmap;
  delete _pJMissileBitmap;
  delete _pTimmyBitmap;
  delete _pTMissileBitmap;
  delete _pSmExplosionBitmap;
  delete _pLgExplosionBitmap;
  delete _pGameOverBitmap;
  
  // Cleanup the background
  delete _pBackground;
  
  // Cleanup the sprites
  pGameEngine->CleanupSprites();

  //Cleanup the sound effects
  Mix_FreeChunk(_mcMissile);
  Mix_FreeChunk(_mcJMissile);
  Mix_FreeChunk(_mcBMissile);
  Mix_FreeChunk(_mcTMissile);
  Mix_FreeChunk(_mcSmExplode);
  Mix_FreeChunk(_mcLgExplode);
  Mix_FreeChunk(_mcGameOver);
  
  //Cleanup the music
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

  // Draw the desert bitmap
  _pDesertBitmap->Draw(renderer, 0, 371);
  
  // Draw the sprites
  pGameEngine->DrawSprites();

  // Draw the number of remaining lives (cars)
  for (int i = 0; i < _iNumLives; i++)
    _pSmCarBitmap->Draw(renderer,
			520 + (_pSmCarBitmap->GetWidth() * i),
			10);

  // Draw the score
  char szText[64];
  SDL_Rect  rect = { 460, 0, 50, 30 };
  sprintf(szText, "%d", _iScore);
  SDL_Color text_color = {255, 255, 255, 255};
  SDL_Texture *text_texture = pGameEngine->DrawText(renderer,
						    szText,
						    _ttfFont,
						    text_color);
  if(text_texture)SDL_RenderCopy(renderer, text_texture, NULL, &rect);  

  
 // Draw the number of remaining lives (cars)
  for (int i = 0; i < _iNumLives; i++)
    _pSmCarBitmap->Draw(renderer,
			520 + (_pSmCarBitmap->GetWidth() * i),
			10);

  // Draw the game over message, if necessary
  if (_bGameOver)
    _pGameOverBitmap->Draw(renderer, 190, 149);
  
  SDL_RenderPresent(renderer);
}

void Game::Cycle()
{
  if (!_bGameOver)
  {
    // Randomly add aliens
    if ((rand() % Game::_iDifficulty) == 0)
      AddAlien();
    
    GameEngine *pGameEngine = GameEngine::GetEngine();
  
    // Update the background
    _pBackground->Update();
  
    // Update the sprites
    pGameEngine->UpdateSprites();
  }
}

void Game::HandleKeys(){
  GameEngine *pGameEngine = GameEngine::GetEngine();
 
  SDL_PumpEvents();
  const Uint8 *state = SDL_GetKeyboardState(NULL);

  //Q
  if (state[SDL_GetScancodeFromKey(SDLK_q)]) {
    exit(0);
  }

  if (!_bGameOver)
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
      SDL_Rect  rcBounds = { 0, 0, 600, 450 };
      SDL_Rect  rcPos = _pCarSprite->GetPosition();
      Sprite* pSprite = new Sprite(_pMissileBitmap, rcBounds, BA_DIE);
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
  if (_bGameOver && state[SDL_SCANCODE_RETURN])
    // Start a new game
    NewGame();
  
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
  GameEngine *pGameEngine = GameEngine::GetEngine();
  
 // See if a player missile and an alien have collided
  Bitmap* pHitter = pSpriteHitter->GetBitmap();
  Bitmap* pHittee = pSpriteHittee->GetBitmap();
  if ((pHitter == _pMissileBitmap && (pHittee == _pBlobboBitmap ||
    pHittee == _pJellyBitmap || pHittee == _pTimmyBitmap)) ||
    (pHittee == _pMissileBitmap && (pHitter == _pBlobboBitmap ||
    pHitter == _pJellyBitmap || pHitter == _pTimmyBitmap)))
  {
    // Play the small explosion sound
    Mix_PlayChannel(-1, _mcSmExplode, 0);
    
    // Kill both sprites
    pSpriteHitter->Kill();
    pSpriteHittee->Kill();

    // Create a large explosion sprite at the alien's position
    SDL_Rect rcBounds = { 0, 0, 600, 450 };
    SDL_Rect rcPos;
    if (pHitter == _pMissileBitmap)
      rcPos = pSpriteHittee->GetPosition();
    else
      rcPos = pSpriteHitter->GetPosition();
    Sprite* pSprite = new Sprite(_pLgExplosionBitmap, rcBounds);
    pSprite->SetNumFrames(8, true);
    pSprite->SetPosition(rcPos.x, rcPos.y);
    pGameEngine->AddSprite(pSprite);

    // Update the score
    _iScore += 25;
    _iDifficulty = max(80 - (_iScore / 20), 20);
  }

  // See if an alien missile has collided with the car
  if ((pHitter == _pCarBitmap && (pHittee == _pBMissileBitmap ||
    pHittee == _pJMissileBitmap || pHittee == _pTMissileBitmap)) ||
    (pHittee == _pCarBitmap && (pHitter == _pBMissileBitmap ||
    pHitter == _pJMissileBitmap || pHitter == _pTMissileBitmap)))
  {
    // Play the large explosion sound
    Mix_PlayChannel(-1, _mcLgExplode, 0);

    // Kill the missile sprite
    if (pHitter == _pCarBitmap)
      pSpriteHittee->Kill();
    else
      pSpriteHitter->Kill();

    // Create a large explosion sprite at the car's position
    SDL_Rect rcBounds = { 0, 0, 600, 480 };
    SDL_Rect rcPos;
    if (pHitter == _pCarBitmap)
      rcPos = pSpriteHitter->GetPosition();
    else
      rcPos = pSpriteHittee->GetPosition();
    Sprite* pSprite = new Sprite(_pLgExplosionBitmap, rcBounds);
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
    }
  }

  return false;
}

void Game::SpriteDying(Sprite* pSprite){
  // See if an alien missile sprite is dying
  if (pSprite->GetBitmap() == _pBMissileBitmap ||
    pSprite->GetBitmap() == _pJMissileBitmap ||
    pSprite->GetBitmap() == _pTMissileBitmap)
  {
    // Play the small explosion sound
    Mix_PlayChannel(-1, _mcSmExplode, 0);

    // Create a small explosion sprite at the missile's position
    SDL_Rect rcBounds = { 0, 0, 600, 450 };
    SDL_Rect rcPos = pSprite->GetPosition();
    Sprite* pSprite = new Sprite(_pSmExplosionBitmap, rcBounds);
    pSprite->SetNumFrames(8, true);
    pSprite->SetPosition(rcPos.x, rcPos.y);
    GameEngine *pGameEngine = GameEngine::GetEngine();
    pGameEngine->AddSprite(pSprite);
  }
}

//-----------------------------------------------------------------
// Functions
//-----------------------------------------------------------------
void Game::NewGame(){
  GameEngine *pGameEngine = GameEngine::GetEngine();
  
  // Clear the sprites
  pGameEngine->CleanupSprites();

  // Create the car sprite
  SDL_Rect rcBounds = { 0, 0, 600, 450 };
  _pCarSprite = new Sprite(_pCarBitmap, rcBounds, BA_WRAP);
  _pCarSprite->SetPosition(300, 405);
  pGameEngine->AddSprite(_pCarSprite);

  // Initialize the game variables
  _iFireInputDelay = 0;
  _iScore = 0;
  _iNumLives = 3;
  Game::_iDifficulty = 80;
  _bGameOver = false;

  // Play the background music
  pGameEngine->PlaySong(_mmMusic);
}

void Game::AddAlien(){
  // Create a new random alien sprite
  SDL_Rect      rcBounds = { 0, 0, 600, 410 };
  AlienSprite*  pSprite;
  switch(rand() % 3)
  {
  case 0:
    // Blobbo
    pSprite = new AlienSprite(_pBlobboBitmap, rcBounds, BA_BOUNCE);
    pSprite->SetNumFrames(8);
    pSprite->SetPosition(((rand() % 2) == 0) ? 0 : 600, rand() % 370);
    pSprite->SetVelocity((rand() % 7) - 2, (rand() % 7) - 2);
    break;
  case 1:
    // Jelly
    pSprite = new AlienSprite(_pJellyBitmap, rcBounds, BA_BOUNCE);
    pSprite->SetNumFrames(8);
    pSprite->SetPosition(rand() % 600, rand() % 370);
    pSprite->SetVelocity((rand() % 5) - 2, (rand() % 5) + 3);
    break;
  case 2:
    // Timmy
    pSprite = new AlienSprite(_pTimmyBitmap, rcBounds, BA_WRAP);
    pSprite->SetNumFrames(8);
    pSprite->SetPosition(rand() % 600, rand() % 370);
    pSprite->SetVelocity((rand() % 7) + 3, 0);
    break;
  }

  // Add the alien sprite
  GameEngine *pGameEngine = GameEngine::GetEngine();
  pGameEngine->AddSprite(pSprite);
}

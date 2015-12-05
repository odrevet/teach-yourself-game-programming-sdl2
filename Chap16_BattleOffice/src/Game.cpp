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

  //init text
  _ttfFont = TTF_OpenFont("res/DejaVuSans.ttf", 12);
  if ( _ttfFont == nullptr ){
    std::cout << " Failed to load font : " << TTF_GetError() << std::endl;
    return false;
  }

  //Hide the mouse pointer
  SDL_ShowCursor(false);
    
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
  _pOfficeBitmap = new Bitmap(renderer, "res/Office.bmp");
  _pTargetBitmap = new Bitmap(renderer, "res/Target.bmp", &scTrans);
  _pPowBitmap = new Bitmap(renderer, "res/Pow.bmp", &scTrans);
  _pGuyBitmaps[0] = new Bitmap(renderer, "res/Guy1.bmp", &scTrans);
  _pGuyBitmaps[1] = new Bitmap(renderer, "res/Guy2.bmp", &scTrans);
  _pGuyBitmaps[2] = new Bitmap(renderer, "res/Guy3.bmp", &scTrans);
  _pGuyBitmaps[3] = new Bitmap(renderer, "res/Guy4.bmp", &scTrans);
  _pGuyBitmaps[4] = new Bitmap(renderer, "res/Guy5.bmp", &scTrans);
  _pSmallGuyBitmap = new Bitmap(renderer, "res/SmallGuy.bmp", &scTrans);
  _pGameOverBitmap = new Bitmap(renderer, "res/GameOver.bmp", &scTrans);

  // Create the target, pow, and guy sprites
  SDL_Rect rcBounds = { 0, 0, 500, 400 };
  _pTargetSprite = new Sprite(_pTargetBitmap, rcBounds, BA_STOP);
  _pTargetSprite->SetZOrder(4);
  pGE->AddSprite(_pTargetSprite);
  _pPowSprite = new Sprite(_pPowBitmap, rcBounds, BA_STOP);
  _pPowSprite->SetZOrder(3);
  _pPowSprite->SetHidden(true);
  pGE->AddSprite(_pPowSprite);
  _pGuySprites[0] = new Sprite(_pGuyBitmaps[0], rcBounds);
  _pGuySprites[0]->SetPosition(92, 175);
  _pGuySprites[0]->SetZOrder(2);
  _pGuySprites[0]->SetHidden(true);
  pGE->AddSprite(_pGuySprites[0]);
  _pGuySprites[1] = new Sprite(_pGuyBitmaps[1], rcBounds);
  _pGuySprites[1]->SetPosition(301, 184);
  _pGuySprites[1]->SetZOrder(2);
  _pGuySprites[1]->SetHidden(true);
  pGE->AddSprite(_pGuySprites[1]);
  _pGuySprites[2] = new Sprite(_pGuyBitmaps[2], rcBounds);
  _pGuySprites[2]->SetPosition(394, 61);
  _pGuySprites[2]->SetZOrder(2);
  _pGuySprites[2]->SetHidden(true);
  pGE->AddSprite(_pGuySprites[2]);
  rcBounds.x = 340;
  _pGuySprites[3] = new Sprite(_pGuyBitmaps[3], rcBounds, BA_WRAP);
  _pGuySprites[3]->SetPosition(500, 10);
  _pGuySprites[3]->SetVelocity(-3, 0);
  _pGuySprites[3]->SetZOrder(1);
  _pGuySprites[3]->SetHidden(true);
  pGE->AddSprite(_pGuySprites[3]);
  rcBounds.x = 385;
  _pGuySprites[4] = new Sprite(_pGuyBitmaps[4], rcBounds, BA_WRAP);
  _pGuySprites[4]->SetPosition(260, 60);
  _pGuySprites[4]->SetVelocity(5, 0);
  _pGuySprites[4]->SetZOrder(1);
  _pGuySprites[4]->SetHidden(true);
  pGE->AddSprite(_pGuySprites[4]);

  // Initialize the remaining global variables
  _iGuyMasterDelay = 50;
  _iHits = 0;
  _iMisses = 0;
  _bGameOver = false;
  
  //Load the music
  _mmMusic = Mix_LoadMUS("res/Music.xm");
  if(_mmMusic==nullptr) cout << "Could not play music: " <<  Mix_GetError();

  //Load the sound effetcs
  _mcWhack = Mix_LoadWAV("res/Whack.wav");
  _mcTaunt = Mix_LoadWAV("res/Taunt.wav");
  _mcBoo = Mix_LoadWAV("res/Boo.wav");
  
  // Play the background music
  pGE->PlaySong(_mmMusic);
}

void Game::End()
{
  GameEngine *pGameEngine = GameEngine::GetEngine();

  // Cleanup the sprites
  pGameEngine->CleanupSprites();

  //Cleanup the music
  Mix_FreeMusic(_mmMusic);
  
  //Cleanup the sound effects
  Mix_FreeChunk(_mcWhack);
  Mix_FreeChunk(_mcTaunt);
  Mix_FreeChunk(_mcBoo);
  
  // Cleanup the bitmaps
  delete _pOfficeBitmap;
  delete _pTargetBitmap;
  delete _pPowBitmap;
  for (int i = 0; i < 5; i++)
    delete _pGuyBitmaps[i];
  delete _pSmallGuyBitmap;
  delete _pGameOverBitmap;

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

  // Draw the background office
  _pOfficeBitmap->Draw(renderer, 0, 0);

  // Draw the sprites
  pGameEngine->DrawSprites();

  // Draw the number of guys who were hit
  char szText[64];
  SDL_Rect  rect = { 237, 360, 50, 50 };
  sprintf(szText, " %d ", _iHits);
  SDL_Color text_color = {120, 120, 120};
  SDL_Texture *text_texture = pGameEngine->DrawText(renderer,
						    szText,
						    _ttfFont,
						    text_color);
  if(text_texture)SDL_RenderCopy(renderer, text_texture, NULL, &rect);
  
  
  // Draw the number of guys who were missed (got away)
  for (int i = 0; i < _iMisses; i++)
    _pSmallGuyBitmap->Draw(renderer,
			   389 + (_pSmallGuyBitmap->GetWidth() * i),
			   359);

  // Draw the game over message, if necessary
  if (_bGameOver)
    _pGameOverBitmap->Draw(renderer, 120, 110);
  
  SDL_RenderPresent(renderer);
}

void Game::Cycle()
{
  GameEngine *pGameEngine = GameEngine::GetEngine();  
  if (!_bGameOver)
  {
    // Randomly show and hide the guys
    for (int i = 0; i < 5; i++)
      if (_pGuySprites[i]->IsHidden())
      {
        if (rand() % 60 == 0)
        {
          // Show the guy
          _pGuySprites[i]->SetHidden(false);

          // Start the countdown delay
          if (i == 3)
          {
            // Start the guy running left
            _iGuyDelay[i] = 80;
            _pGuySprites[i]->SetPosition(500, 10);
          }
          else if (i == 4)
          {
            // Start the guy running right
            _iGuyDelay[i] = 45;
            _pGuySprites[i]->SetPosition(260, 60);
          }
          else
            // Start the stationary guys
            _iGuyDelay[i] = 20 + (rand() % _iGuyMasterDelay);
        }
      }
      else
      {
        if (--_iGuyDelay[i] == 0)
        {
          // Play a sound for the guy getting away
	  Mix_PlayChannel(-1, _mcTaunt, 0 );
	  
          // Hide the guy
          _pGuySprites[i]->SetHidden(true);

          // Increment the misses
          if (++_iMisses == 5)
          {
            // Play a sound for the game ending
	    Mix_PlayChannel(-1, _mcBoo, 0 );

            // End the game
            for (int i = 0; i < 5; i++)
              _pGuySprites[i]->SetHidden(true);
            _bGameOver = true;

            // Pause the background music
            pGameEngine->PauseSong();
          }
        }
      }

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
}

void Game::MouseButtonDown(int x, int y, bool bLeft)
{
  GameEngine *pGameEngine = GameEngine::GetEngine();
  
  // Only check the left mouse button
  if (!_bGameOver && bLeft)
  {
    // Temporarily hide the target and pow sprites
    _pTargetSprite->SetHidden(true);
    _pPowSprite->SetHidden(true);

    // See if a guy sprite was clicked
    Sprite* pSprite;
    if ((pSprite = pGameEngine->IsPointInSprite(x, y)) != NULL)
    {
      // Play a sound for hitting the guy
       Mix_PlayChannel(-1, _mcWhack, 0 );

      // Position and show the pow sprite
      _pPowSprite->SetPosition(x - (_pPowSprite->GetWidth() / 2),
        y - (_pPowSprite->GetHeight() / 2));
      _pPowSprite->SetHidden(false);

      // Hide the guy that was clicked
      pSprite->SetHidden(true);

      // Increment the hits and make the game harder, if necessary
      if ((++_iHits % 5) == 0)
        if (--_iGuyMasterDelay == 0)
          _iGuyMasterDelay = 1;
    }

    // Show the target sprite again
    _pTargetSprite->SetHidden(false);
  }
  else if (_bGameOver && !bLeft)
  {
    // Start a new game
    _bGameOver = false;
    _iHits = 0;
    _iMisses = 0;

    // Restart the background music
    pGameEngine->PlaySong(_mmMusic);
  }
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

bool Game::SpriteCollision(Sprite* pSpriteHitter, Sprite* pSpriteHittee){
  return false;
}

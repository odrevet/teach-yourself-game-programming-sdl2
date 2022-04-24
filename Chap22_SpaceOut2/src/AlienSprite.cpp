//-----------------------------------------------------------------
// Alien Sprite Object
// C++ Source - AlienSprite.cpp
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "AlienSprite.h"

//-----------------------------------------------------------------
// AlienSprite Constructor(s)/Destructor
//-----------------------------------------------------------------
AlienSprite::AlienSprite(Bitmap *pBitmap, SDL_Rect &rcBounds,
                         BOUNDSACTION baBoundsAction) : Sprite(pBitmap, rcBounds,
                                                               baBoundsAction)
{
}

AlienSprite::~AlienSprite()
{
}

//-----------------------------------------------------------------
// AlienSprite General Methods
//-----------------------------------------------------------------
SPRITEACTION AlienSprite::Update()
{
  // Call the base sprite Update() method
  SPRITEACTION saSpriteAction;
  saSpriteAction = Sprite::Update();

  // See if the alien should fire a missile
  if ((rand() % (Game::_iDifficulty / 2)) == 0)
    saSpriteAction |= SA_ADDSPRITE;

  return saSpriteAction;
}

Sprite *AlienSprite::AddSprite()
{
  // Create a new missile sprite
  SDL_Rect rcBounds = {0, 0, 640, 410};
  SDL_Rect rcPos = GetPosition();

  Sprite *pSprite = NULL;
  if (GetBitmap() == Game::_pBlobboBitmap)
  {
    // Blobbo missile
    pSprite = new Sprite(Game::_pBMissileBitmap, rcBounds, BA_DIE);
    pSprite->SetVelocity(0, 7);
  }
  else if (GetBitmap() == Game::_pJellyBitmap)
  {
    // Jelly missile
    pSprite = new Sprite(Game::_pJMissileBitmap, rcBounds, BA_DIE);
    pSprite->SetVelocity(0, 5);
  }
  else
  {
    // Timmy missile
    pSprite = new Sprite(Game::_pTMissileBitmap, rcBounds, BA_DIE);
    pSprite->SetVelocity(0, 3);
  }

  // Set the missile sprite's position and return it
  pSprite->SetPosition(rcPos.x + (GetWidth() / 2), rcPos.y);
  return pSprite;
}

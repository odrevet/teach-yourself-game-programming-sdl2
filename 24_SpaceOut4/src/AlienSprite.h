//-----------------------------------------------------------------
// Alien Sprite Object
// C++ Header - AlienSprite.h
//-----------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include <SDL.h>
#include "Sprite.h"
#include "Game.h"

//-----------------------------------------------------------------
// AlienSprite Class
//-----------------------------------------------------------------
class AlienSprite : public Sprite
{
public:
  // Constructor(s)/Destructor
  AlienSprite(Bitmap *pBitmap, SDL_Rect &rcBounds,
              BOUNDSACTION baBoundsAction = BA_STOP);
  virtual ~AlienSprite();

  // General Methods
  virtual SPRITEACTION Update();
  virtual Sprite *AddSprite();
};

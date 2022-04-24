//-----------------------------------------------------------------
// Alien Sprite Object
// C++ Header - AlienSprite.h
//-----------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include <SDL.h>

#include <Sprite.h>

#include "Game.h"

using namespace TYGP;

//-----------------------------------------------------------------
// AlienSprite Class
//-----------------------------------------------------------------
class AlienSprite : public Sprite
{
public:
  // Constructor(s)/Destructor
  AlienSprite(Image *pImage, SDL_Rect &rcBounds,
              BOUNDSACTION baBoundsAction = BA_STOP);
  virtual ~AlienSprite();

  // General Methods
  virtual SPRITEACTION Update();
  virtual Sprite *AddSprite();
};

//-----------------------------------------------------------------
// Background Object
// C++ Header - Background.h
//-----------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include <SDL.h>
#include <algorithm>

#include "Bitmap.h"

//-----------------------------------------------------------------
// Background Class
//-----------------------------------------------------------------
class Background
{
protected:
  // Member Variables
  int m_iWidth, m_iHeight;
  SDL_Color m_crColor;
  Bitmap *m_pBitmap;

public:
  // Constructor(s)/Destructor
  Background(int iWidth, int iHeight, SDL_Color crColor);
  Background(Bitmap *pBitmap);
  virtual ~Background();

  // General Methods
  virtual void Update();
  virtual void Draw(SDL_Renderer *renderer);

  // Accessor Methods
  int GetWidth() { return m_iWidth; };
  int GetHeight() { return m_iHeight; };
};

//-----------------------------------------------------------------
// Starry Background Class
//-----------------------------------------------------------------
class StarryBackground : Background
{
protected:
  // Member Variables
  int m_iNumStars;
  int m_iTwinkleDelay;
  SDL_Point m_ptStars[100];
  SDL_Color m_crStarColors[100];

public:
  // Constructor(s)/Destructor
  StarryBackground(int iWidth, int iHeight, int iNumStars = 100,
                   int iTwinkleDelay = 50);
  virtual ~StarryBackground();

  // General Methods
  virtual void Update();
  virtual void Draw(SDL_Renderer *renderer);
};

//-----------------------------------------------------------------
// Sprite Object
// C++ Header - Sprite.h
//-----------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include <SDL.h>
#include <algorithm>

#include "Bitmap.h"

//-----------------------------------------------------------------
// Custom Data Types
//-----------------------------------------------------------------
typedef int BOUNDSACTION;
const BOUNDSACTION BA_STOP = 0,
                   BA_WRAP = 1,
                   BA_BOUNCE = 2,
                   BA_DIE = 3;

//-----------------------------------------------------------------
// Sprite Class
//-----------------------------------------------------------------
class Sprite
{
protected:
  // Member Variables
  Bitmap *m_pBitmap;
  SDL_Rect m_rcPosition;
  SDL_Point m_ptVelocity;
  int m_iZOrder;
  SDL_Rect m_rcBounds;
  BOUNDSACTION m_baBoundsAction;
  bool m_bHidden;

public:
  // Constructor(s)/Destructor
  Sprite(Bitmap *pBitmap);
  Sprite(Bitmap *pBitmap, SDL_Rect &rcBounds,
         BOUNDSACTION baBoundsAction = BA_STOP);
  Sprite(Bitmap *pBitmap, SDL_Point ptPosition, SDL_Point ptVelocity, int iZOrder,
         SDL_Rect &rcBounds, BOUNDSACTION baBoundsAction = BA_STOP);
  virtual ~Sprite();

  // General Methods
  virtual void Update();
  void Draw(SDL_Renderer *renderer);
  bool IsPointInside(int x, int y);

  // Accessor Methods
  SDL_Rect &GetPosition() { return m_rcPosition; };
  void SetPosition(int x, int y);
  void SetPosition(SDL_Point ptPosition);
  void SetPosition(SDL_Rect &rcPosition)
  {
    memcpy(&m_rcPosition, &rcPosition, sizeof(SDL_Rect));
  };
  void OffsetPosition(int x, int y);
  SDL_Point GetVelocity() { return m_ptVelocity; };
  void SetVelocity(int x, int y);
  void SetVelocity(SDL_Point ptVelocity);
  bool GetZOrder() { return m_iZOrder; };
  void SetZOrder(int iZOrder) { m_iZOrder = iZOrder; };
  void SetBounds(SDL_Rect &rcBounds) { memcpy(&m_rcBounds, &rcBounds, sizeof(SDL_Rect)); };
  void SetBoundsAction(BOUNDSACTION ba) { m_baBoundsAction = ba; };
  bool IsHidden() { return m_bHidden; };
  void SetHidden(bool bHidden) { m_bHidden = bHidden; };
  int GetWidth() { return m_pBitmap->GetWidth(); };
  int GetHeight() { return m_pBitmap->GetHeight(); };
};

//-----------------------------------------------------------------
// Sprite Inline General Methods
//-----------------------------------------------------------------
inline bool Sprite::IsPointInside(int x, int y)
{
  bool point_in_rect = false;
  if (x > m_rcPosition.x && x < m_rcPosition.x + m_rcPosition.w &&
      y > m_rcPosition.y && y < m_rcPosition.y + m_rcPosition.h)
  {
    point_in_rect = true;
  }

  return point_in_rect;
}

//-----------------------------------------------------------------
// Sprite Inline Accessor Methods
//-----------------------------------------------------------------
inline void Sprite::SetPosition(int x, int y)
{
  m_rcPosition.x = x;
  m_rcPosition.y = y;
}

inline void Sprite::SetPosition(SDL_Point ptPosition)
{
  m_rcPosition.x = ptPosition.x;
  m_rcPosition.y = ptPosition.y;
}

inline void Sprite::OffsetPosition(int x, int y)
{
  m_rcPosition.x = x;
  m_rcPosition.y = y;
}

inline void Sprite::SetVelocity(int x, int y)
{
  m_ptVelocity.x = x;
  m_ptVelocity.y = y;
}

inline void Sprite::SetVelocity(SDL_Point ptVelocity)
{
  m_ptVelocity.x = ptVelocity.x;
  m_ptVelocity.y = ptVelocity.y;
}

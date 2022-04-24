//-----------------------------------------------------------------
// Sprite Object
// C++ Source - Sprite.cpp
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Sprite.h"

//-----------------------------------------------------------------
// Sprite Constructor(s)/Destructor
//-----------------------------------------------------------------
Sprite::Sprite(Bitmap *pBitmap)
{
  // Initialize the member variables
  m_pBitmap = pBitmap;
  m_rcPosition.x = 0;
  m_rcPosition.y = 0;
  m_rcPosition.w = pBitmap->GetWidth();
  m_rcPosition.h = pBitmap->GetHeight();
  m_ptVelocity.x = m_ptVelocity.y = 0;
  m_iZOrder = 0;
  m_rcBounds.x = 0;
  m_rcBounds.y = 0;
  m_rcBounds.w = 640;
  m_rcBounds.h = 480;
  m_baBoundsAction = BA_STOP;
  m_bHidden = false;
}

Sprite::Sprite(Bitmap *pBitmap, SDL_Rect &rcBounds, BOUNDSACTION baBoundsAction)
{
  // Calculate a random position
  int iXPos = rand() % (rcBounds.w - rcBounds.x);
  int iYPos = rand() % (rcBounds.h - rcBounds.y);

  // Initialize the member variables
  m_pBitmap = pBitmap;
  m_rcPosition.x = iXPos;
  m_rcPosition.y = iYPos;
  m_rcPosition.w = pBitmap->GetWidth();
  m_rcPosition.h = pBitmap->GetHeight();
  m_ptVelocity.x = m_ptVelocity.y = 0;
  m_iZOrder = 0;
  memcpy(&m_rcBounds, &rcBounds, sizeof(SDL_Rect));
  m_baBoundsAction = baBoundsAction;
  m_bHidden = false;
}

Sprite::Sprite(Bitmap *pBitmap, SDL_Point ptPosition, SDL_Point ptVelocity, int iZOrder,
               SDL_Rect &rcBounds, BOUNDSACTION baBoundsAction)
{
  // Initialize the member variables
  m_pBitmap = pBitmap;
  m_rcPosition.x = ptPosition.x;
  m_rcPosition.y = ptPosition.y;
  m_rcPosition.w = pBitmap->GetWidth();
  m_rcPosition.h = pBitmap->GetHeight();
  m_ptVelocity = ptPosition;
  m_iZOrder = iZOrder;
  memcpy(&m_rcBounds, &rcBounds, sizeof(SDL_Rect));
  m_baBoundsAction = baBoundsAction;
  m_bHidden = false;
}

Sprite::~Sprite()
{
}

//-----------------------------------------------------------------
// Sprite General Methods
//-----------------------------------------------------------------
void Sprite::Update()
{
  // Update the position
  SDL_Point ptNewPosition, ptSpriteSize;
  ptNewPosition.x = m_rcPosition.x + m_ptVelocity.x;
  ptNewPosition.y = m_rcPosition.y + m_ptVelocity.y;

  ptSpriteSize.x = m_rcPosition.w;
  ptSpriteSize.y = m_rcPosition.h;

  // Check the bounds
  // Wrap?
  if (m_baBoundsAction == BA_WRAP)
  {
    if ((ptNewPosition.x + ptSpriteSize.x) < m_rcBounds.x)
      ptNewPosition.x = m_rcBounds.w;
    else if (ptNewPosition.x > m_rcBounds.w)
      ptNewPosition.x = m_rcBounds.x - ptSpriteSize.x;
    if ((ptNewPosition.y + ptSpriteSize.y) < m_rcBounds.y)
      ptNewPosition.y = m_rcBounds.h;
    else if (ptNewPosition.y > m_rcBounds.h)
      ptNewPosition.y = m_rcBounds.y - ptSpriteSize.y;
  }
  // Bounce?
  else if (m_baBoundsAction == BA_BOUNCE)
  {
    bool bBounce = false;
    SDL_Point ptNewVelocity = m_ptVelocity;
    if (ptNewPosition.x < m_rcBounds.x)
    {
      bBounce = true;
      ptNewPosition.x = m_rcBounds.x;
      ptNewVelocity.x = -ptNewVelocity.x;
    }
    else if ((ptNewPosition.x + ptSpriteSize.x) > m_rcBounds.w)
    {
      bBounce = true;
      ptNewPosition.x = m_rcBounds.w - ptSpriteSize.x;
      ptNewVelocity.x = -ptNewVelocity.x;
    }
    if (ptNewPosition.y < m_rcBounds.y)
    {
      bBounce = true;
      ptNewPosition.y = m_rcBounds.y;
      ptNewVelocity.y = -ptNewVelocity.y;
    }
    else if ((ptNewPosition.y + ptSpriteSize.y) > m_rcBounds.h)
    {
      bBounce = true;
      ptNewPosition.y = m_rcBounds.h - ptSpriteSize.y;
      ptNewVelocity.y = -ptNewVelocity.y;
    }
    if (bBounce)
      SetVelocity(ptNewVelocity);
  }
  // Stop (default)
  else
  {
    if (ptNewPosition.x < m_rcBounds.x ||
        ptNewPosition.x > (m_rcBounds.w - ptSpriteSize.x))
    {
      ptNewPosition.x = std::max(m_rcBounds.x, std::min(ptNewPosition.x,
                                                        m_rcBounds.w - ptSpriteSize.x));
      SetVelocity(0, 0);
    }
    if (ptNewPosition.y < m_rcBounds.y ||
        ptNewPosition.y > (m_rcBounds.h - ptSpriteSize.y))
    {
      ptNewPosition.y = std::max(m_rcBounds.y, std::min(ptNewPosition.y,
                                                        m_rcBounds.h - ptSpriteSize.y));
      SetVelocity(0, 0);
    }
  }
  SetPosition(ptNewPosition);
}

void Sprite::Draw(SDL_Renderer *renderer)
{
  // Draw the sprite if it isn't hidden
  if (m_pBitmap != NULL && !m_bHidden)
    m_pBitmap->Draw(renderer, m_rcPosition.x, m_rcPosition.y);
#ifdef DEBUG
  SDL_RenderDrawRect(renderer, &this->m_rcBounds);
  SDL_RenderDrawRect(renderer, &this->m_rcPosition);
#endif
}

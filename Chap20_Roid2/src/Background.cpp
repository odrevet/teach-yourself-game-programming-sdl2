//-----------------------------------------------------------------
// Background Object
// C++ Source - Background.cpp
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Background.h"

//-----------------------------------------------------------------
// Background Constructor(s)/Destructor
//-----------------------------------------------------------------
Background::Background(int iWidth, int iHeight, SDL_Color crColor)
{
  // Initialize the member variables
  m_iWidth = iWidth;
  m_iHeight = iHeight;
  m_crColor = crColor;
  m_pBitmap = NULL;
}

Background::Background(Bitmap *pBitmap)
{
  // Initialize the member variables
  m_crColor = {0, 0, 0};
  m_pBitmap = pBitmap;
  m_iWidth = pBitmap->GetWidth();
  m_iHeight = pBitmap->GetHeight();
}

Background::~Background()
{
}

//-----------------------------------------------------------------
// Background General Methods
//-----------------------------------------------------------------
void Background::Update()
{
  // Do nothing since the basic background is not animated
}

void Background::Draw(SDL_Renderer *renderer)
{
  // Draw the background
  if (m_pBitmap != NULL)
    m_pBitmap->Draw(renderer, 0, 0);
  else
  {
    SDL_Rect rect = {0, 0, m_iWidth, m_iHeight};
    SDL_SetRenderDrawColor(renderer,
                           m_crColor.r,
                           m_crColor.g,
                           m_crColor.b,
                           255);
    SDL_RenderFillRect(renderer, &rect);
  }
}

//-----------------------------------------------------------------
// StarryBackground Constructor
//-----------------------------------------------------------------
StarryBackground::StarryBackground(int iWidth, int iHeight, int iNumStars,
                                   int iTwinkleDelay) : Background(iWidth, iHeight, {0, 0, 0})
{
  // Initialize the member variables
  m_iNumStars = std::min(iNumStars, 100);
  m_iTwinkleDelay = iTwinkleDelay;

  // Create the stars
  for (int i = 0; i < iNumStars; i++)
  {
    m_ptStars[i].x = rand() % iWidth;
    m_ptStars[i].y = rand() % iHeight;
    SDL_Color color = {128, 128, 128};
    m_crStarColors[i] = color;
  }
}

StarryBackground::~StarryBackground()
{
}

//-----------------------------------------------------------------
// StarryBackground General Methods
//-----------------------------------------------------------------
void StarryBackground::Update()
{
  // Randomly change the shade of the stars so that they twinkle
  Uint8 iRGB;
  for (int i = 0; i < m_iNumStars; i++)
    if ((rand() % m_iTwinkleDelay) == 0)
    {
      iRGB = rand() % 256;
      SDL_Color c = {iRGB, iRGB, iRGB};
      m_crStarColors[i] = c;
    }
}

void StarryBackground::Draw(SDL_Renderer *renderer)
{
  // Draw the solid black background
  SDL_Rect rect = {0, 0, m_iWidth, m_iHeight};
  SDL_SetRenderDrawColor(renderer,
                         m_crColor.r,
                         m_crColor.g,
                         m_crColor.b,
                         255);
  SDL_RenderFillRect(renderer, &rect);

  // Draw the stars
  for (int i = 0; i < m_iNumStars; i++)
  {
    SDL_SetRenderDrawColor(renderer,
                           m_crStarColors[i].r,
                           m_crStarColors[i].g,
                           m_crStarColors[i].b,
                           255);
    SDL_RenderDrawPoint(renderer, m_ptStars[i].x, m_ptStars[i].y);
  }
}

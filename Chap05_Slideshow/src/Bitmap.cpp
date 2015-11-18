//-----------------------------------------------------------------
// Bitmap Object
// C++ Source - Bitmap.cpp
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Bitmap.h"

//-----------------------------------------------------------------
// Bitmap Constructor(s)/Destructor
//-----------------------------------------------------------------
Bitmap::Bitmap()
  : m_hBitmap(NULL), m_iWidth(0), m_iHeight(0)
{
}

// Create a bitmap from a file
Bitmap::Bitmap(SDL_Renderer* renderer, const char* szFileName)
  : m_hBitmap(NULL), m_iWidth(0), m_iHeight(0)
{
  SDL_Surface *surface = IMG_Load(szFileName);
  if (!surface){
    //ERR
  }

  this->m_iWidth = surface->w;
  this->m_iHeight = surface->h;
    
  this->m_hBitmap = SDL_CreateTextureFromSurface(renderer,
						 surface);
  
  SDL_FreeSurface(surface);      
}

Bitmap::~Bitmap()
{
  Free();
}

//-----------------------------------------------------------------
// Bitmap Helper Methods
//-----------------------------------------------------------------
void Bitmap::Free()
{
  // Delete the bitmap graphics object
  if (m_hBitmap != NULL)
  {
    SDL_DestroyTexture(this->m_hBitmap);
    m_hBitmap = NULL;
  }
}

void Bitmap::Draw(SDL_Renderer* renderer, int x, int y)
{
  if (m_hBitmap != NULL)
  { 
    SDL_Rect rect_dest = {x, y, GetWidth(), GetHeight()};
    SDL_RenderCopy(renderer,
		   this->m_hBitmap,
		   NULL,
		   &rect_dest);
  }
}

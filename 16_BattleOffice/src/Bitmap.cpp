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
Bitmap::Bitmap(SDL_Renderer *renderer, const char *szFileName, SDL_Color *scTransColor)
    : m_hBitmap(NULL), m_iWidth(0), m_iHeight(0)
{
  SDL_Surface *surface = IMG_Load(szFileName);
  if (!surface)
  {
    std::cout << "Error loading " << szFileName << ": " << SDL_GetError() << std::endl;
  }

  this->m_iWidth = surface->w;
  this->m_iHeight = surface->h;

  // transparancy
  if (scTransColor != nullptr)
  {
    int retcode = SDL_SetColorKey(surface,
                                  SDL_TRUE,
                                  SDL_MapRGB(surface->format,
                                             scTransColor->r,
                                             scTransColor->g,
                                             scTransColor->b));
    if (retcode < 0)
      std::cout << SDL_GetError() << std::endl;
  }

  // create texture
  this->m_hBitmap = SDL_CreateTextureFromSurface(renderer,
                                                 surface);

  // set alpha
  if (scTransColor != nullptr && scTransColor->a < 0xFF)
  {
    SDL_SetTextureAlphaMod(this->m_hBitmap, scTransColor->a);
  }

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

void Bitmap::Draw(SDL_Renderer *renderer, int x, int y)
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

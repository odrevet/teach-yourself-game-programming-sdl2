//-----------------------------------------------------------------
// Image Object
// C++ Source - Image.cpp
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Image.h"

namespace TYGP
{
  //-----------------------------------------------------------------
  // Image Constructor(s)/Destructor
  //-----------------------------------------------------------------
  Image::Image()
      : m_hImage(NULL), m_iWidth(0), m_iHeight(0)
  {
  }

  // Create a bitmap from a file
  Image::Image(SDL_Renderer *renderer, const char *szFileName, SDL_Color *scTransColor)
      : m_hImage(NULL), m_iWidth(0), m_iHeight(0)
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
    this->m_hImage = SDL_CreateTextureFromSurface(renderer,
                                                  surface);

    // set alpha
    if (scTransColor != nullptr && scTransColor->a < 0xFF)
    {
      SDL_SetTextureAlphaMod(this->m_hImage, scTransColor->a);
    }

    SDL_FreeSurface(surface);
  }

  Image::~Image()
  {
    Free();
  }

  //-----------------------------------------------------------------
  // Image Helper Methods
  //-----------------------------------------------------------------
  void Image::Free()
  {
    // Delete the bitmap graphics object
    if (m_hImage != NULL)
    {
      SDL_DestroyTexture(this->m_hImage);
      m_hImage = NULL;
    }
  }

  void Image::Draw(SDL_Renderer *renderer, int x, int y)
  {
    if (m_hImage != NULL)
    {
      SDL_Rect rect_dest = {x, y, GetWidth(), GetHeight()};
      SDL_RenderCopy(renderer,
                     this->m_hImage,
                     NULL,
                     &rect_dest);
    }
  }

  void Image::DrawPart(SDL_Renderer *renderer,
                       int x,
                       int y,
                       int xPart,
                       int yPart,
                       int wPart,
                       int hPart)
  {
    if (m_hImage != NULL)
    {
      SDL_Rect rect_src = {xPart, yPart, wPart, hPart};
      SDL_Rect rect_dest = {x, y, wPart, hPart};

      SDL_RenderCopy(renderer,
                     this->m_hImage,
                     &rect_src,
                     &rect_dest);
    }
  }
}

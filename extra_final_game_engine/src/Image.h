//-----------------------------------------------------------------
// Image Object
// C++ Header - Image.h
//-----------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include <SDL.h>
#include <SDL_image.h>

#include <iostream>

namespace TYGP
{
  //-----------------------------------------------------------------
  // Image Class
  //-----------------------------------------------------------------
  class Image
  {
  protected:
    // Member Variables
    SDL_Texture *m_hImage;
    int m_iWidth, m_iHeight;

    // Helper Methods
    void Free();

  public:
    // Constructor(s)/Destructor
    Image();
    Image(SDL_Renderer *renderer,
          const char *szFileNamebool,
          SDL_Color *scTransColor = nullptr);
    virtual ~Image();

    // General Methods
    void Draw(SDL_Renderer *renderer, int x, int y);
    void DrawPart(SDL_Renderer *renderer,
                  int x,
                  int y,
                  int xPart,
                  int yPart,
                  int wPart,
                  int hPart);
    int GetWidth() { return m_iWidth; };
    int GetHeight() { return m_iHeight; };
  };
}

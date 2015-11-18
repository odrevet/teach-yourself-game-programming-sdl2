//-----------------------------------------------------------------
// Bitmap Object
// C++ Header - Bitmap.h
//-----------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include <SDL.h>
#include <SDL_image.h>

//-----------------------------------------------------------------
// Bitmap Class
//-----------------------------------------------------------------
class Bitmap
{
protected:
  // Member Variables
  SDL_Texture* m_hBitmap;
  int     m_iWidth, m_iHeight;

  // Helper Methods
  void Free();

public:
  // Constructor(s)/Destructor
  Bitmap();
  Bitmap(SDL_Renderer* renderer, const char* szFileName);
  virtual ~Bitmap();

  // General Methods
  void Draw(SDL_Renderer* renderer, int x, int y);
  int  GetWidth() { return m_iWidth; };
  int  GetHeight() { return m_iHeight; };
};

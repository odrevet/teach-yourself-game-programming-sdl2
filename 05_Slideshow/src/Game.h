#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <iostream>

#include "IGame.h"
#include "GameEngine.h"
#include "Bitmap.h"

class Game : public IGame
{
public:
  ~Game();
  bool Initialize();
  void Start();
  void End();
  void Activate();
  void Deactivate();
  void Paint();
  void Cycle();

  static const int _iNUMSLIDES = 6;
  Bitmap *_pSlides[_iNUMSLIDES];
  int _iCurSlide;
};

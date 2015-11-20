#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <iostream>
#include <algorithm> 

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
  void HandleKeys();
  void MouseButtonDown(int x, int y, bool bLeft);
  void MouseButtonUp(int x, int y, bool bLeft);
  void MouseMove(int x, int y);
  
  const int   _iMAXSPEED = 8;
  Bitmap*     _pBackground;
  Bitmap*     _pSaucer;
  int         _iSaucerX, _iSaucerY;
  int         _iSpeedX, _iSpeedY;  
};

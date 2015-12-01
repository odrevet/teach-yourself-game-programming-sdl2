#pragma once

#include <SDL.h>

#include <iostream>
#include <algorithm> 

#include "IGame.h"
#include "GameEngine.h"
#include "Bitmap.h"

using namespace std;

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
  void HandleJoystick(JOYSTATE jsJoystickState);
  
  const int   _iMAXSPEED = 8;
  Bitmap*     _pBackground;
  Bitmap*     _pSaucer[2];
  int         _iSaucerX, _iSaucerY;
  int         _iSpeedX, _iSpeedY;
  bool        _bSaucerFlame;
};

#pragma once

#include <SDL.h>

#include <iostream>
#include <algorithm>
#include <ctime>

#include "IGame.h"
#include "GameEngine.h"
#include "Bitmap.h"
#include "Sprite.h"

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

  Bitmap *_pForestBitmap;
  Bitmap *_pGolfBallBitmap;
  Sprite *_pGolfBallSprite[3];
  bool _bDragging;
  int _iDragBall;
};

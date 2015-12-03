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
  bool SpriteCollision(Sprite* pSpriteHitter, Sprite* pSpriteHittee);

  void MoveChicken(int iXDistance, int iYDistance);
    
  Bitmap*     _pHighwayBitmap;
  Bitmap*     _pChickenBitmap;
  Bitmap*     _pCarBitmaps[4];
  Bitmap*     _pChickenHeadBitmap;
  Sprite*     _pChickenSprite;
  int         _iInputDelay;
  int         _iNumLives;
  int         _iScore;
  bool        _bGameOver;
 
};

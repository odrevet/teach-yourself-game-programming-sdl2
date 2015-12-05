#pragma once

#include <SDL.h>
#include <SDL_mixer.h>

#include <iostream>
#include <algorithm>
#include <ctime>

#include "IGame.h"
#include "GameEngine.h"
#include "Bitmap.h"
#include "Sprite.h"
#include "Background.h"

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
  void SpriteDying(Sprite* pSprite);
  void UpdateSaucer();
  
  Bitmap*           _pAsteroidBitmap;
  Bitmap*           _pSaucerBitmap;
  StarryBackground* _pBackground;
  Sprite*           _pAsteroids[3];
  Sprite*           _pSaucer;

};

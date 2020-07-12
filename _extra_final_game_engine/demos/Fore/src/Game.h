#pragma once

#include <SDL.h>

#include <iostream>
#include <algorithm>
#include <ctime>

#include <IGame.h>
#include <GameEngine.h>
#include <Image.h>
#include <Sprite.h>

using namespace std;
using namespace TYGP;

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
  bool HandleKeys();
  void MouseButtonDown(int x, int y, bool bLeft);
  void MouseButtonUp(int x, int y, bool bLeft);
  void MouseMove(int x, int y);
  void HandleJoystick(JOYSTATE jsJoystickState);
  bool SpriteCollision(Sprite* pSpriteHitter, Sprite* pSpriteHittee);
  void SpriteDying(Sprite* pSprite);

  Image*     _pForestImage;
  Image*     _pGolfBallImage;
  Sprite*     _pDragSprite;
};

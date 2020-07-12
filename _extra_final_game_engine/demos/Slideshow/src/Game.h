#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <iostream>

#include <IGame.h>
#include <GameEngine.h>
#include <Image.h>

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
  bool SpriteCollision(Sprite* pSpriteHitter,
		       Sprite* pSpriteHittee);
  void SpriteDying(Sprite* pSprite);
  
  static const int   _iNUMSLIDES = 6;
  Image*     _pSlides[_iNUMSLIDES];
  int         _iCurSlide;
};

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
  
  void NewGame();
  void AddMeteor();
 
  Bitmap*           _pGroundBitmap;
  Bitmap*           _pTargetBitmap;
  Bitmap*           _pCityBitmap;
  Bitmap*           _pMeteorBitmap;
  Bitmap*           _pMissileBitmap;
  Bitmap*           _pExplosionBitmap;
  Bitmap*           _pGameOverBitmap;
  StarryBackground* _pBackground;
  Sprite*           _pTargetSprite;
  int               _iNumCities, _iScore, _iDifficulty;
  bool              _bGameOver;

  TTF_Font*          _ttfFont;
  Mix_Music*        _mmMusic;
  Mix_Chunk*        _mcFire;
  Mix_Chunk*        _mcExplode;
  Mix_Chunk*        _mcBigExplode;

};

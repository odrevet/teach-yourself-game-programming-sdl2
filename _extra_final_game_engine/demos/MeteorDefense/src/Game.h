#pragma once

#include <SDL.h>
#include <SDL_mixer.h>

#include <iostream>
#include <algorithm>
#include <ctime>

#include "IGame.h"
#include "GameEngine.h"
#include "Image.h"
#include "Sprite.h"
#include "Background.h"

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
  
  void NewGame();
  void AddMeteor();
 
  Image*           _pGroundImage;
  Image*           _pTargetImage;
  Image*           _pCityImage;
  Image*           _pMeteorImage;
  Image*           _pMissileImage;
  Image*           _pExplosionImage;
  Image*           _pGameOverImage;
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

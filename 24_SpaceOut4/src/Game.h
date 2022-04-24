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

#include "AlienSprite.h"

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
  bool HandleKeys();
  void MouseButtonDown(int x, int y, bool bLeft);
  void MouseButtonUp(int x, int y, bool bLeft);
  void MouseMove(int x, int y);
  void HandleJoystick(JOYSTATE jsJoystickState);
  bool SpriteCollision(Sprite *pSpriteHitter, Sprite *pSpriteHittee);
  void SpriteDying(Sprite *pSprite);

  void NewGame();
  void AddAlien();
  void UpdateHiScores();
  bool ReadHiScores();
  bool WriteHiScores();

  Bitmap *_pSplashBitmap;
  Bitmap *_pDesertBitmap;
  Bitmap *_pCarBitmap;
  Bitmap *_pSmCarBitmap;
  Bitmap *_pMissileBitmap;
  static Bitmap *_pBlobboBitmap;
  static Bitmap *_pBMissileBitmap;
  static Bitmap *_pJellyBitmap;
  static Bitmap *_pJMissileBitmap;
  static Bitmap *_pTimmyBitmap;
  static Bitmap *_pTMissileBitmap;
  Bitmap *_pSmExplosionBitmap;
  Bitmap *_pLgExplosionBitmap;
  Bitmap *_pGameOverBitmap;
  StarryBackground *_pBackground;
  Sprite *_pCarSprite;
  int _iFireInputDelay;
  int _iNumLives, _iScore;
  static int _iDifficulty;
  bool _bGameOver;
  int _iGameOverDelay;
  bool _bDemo;
  int _iHiScores[5];

  Mix_Music *_mmMusic;
  Mix_Chunk *_mcMissile;
  Mix_Chunk *_mcJMissile;
  Mix_Chunk *_mcBMissile;
  Mix_Chunk *_mcTMissile;
  Mix_Chunk *_mcSmExplode;
  Mix_Chunk *_mcLgExplode;
  Mix_Chunk *_mcGameOver;

  TTF_Font *_ttfFont;
};

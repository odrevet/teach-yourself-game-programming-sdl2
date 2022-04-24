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
  bool SpriteCollision(Sprite *pSpriteHitter, Sprite *pSpriteHittee);

  TTF_Font *_ttfFont;
  Mix_Music *_mmMusic;
  Mix_Chunk *_mcWhack;
  Mix_Chunk *_mcTaunt;
  Mix_Chunk *_mcBoo;
  Bitmap *_pOfficeBitmap;
  Bitmap *_pTargetBitmap;
  Bitmap *_pPowBitmap;
  Bitmap *_pGuyBitmaps[5];
  Bitmap *_pSmallGuyBitmap;
  Bitmap *_pGameOverBitmap;
  Sprite *_pTargetSprite;
  Sprite *_pPowSprite;
  Sprite *_pGuySprites[5];
  int _iGuyDelay[5];
  int _iGuyMasterDelay;
  int _iHits;
  int _iMisses;
  bool _bGameOver;
};

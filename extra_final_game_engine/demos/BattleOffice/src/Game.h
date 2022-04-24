#pragma once

#include <SDL.h>
#include <SDL_mixer.h>

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
  bool SpriteCollision(Sprite *pSpriteHitter, Sprite *pSpriteHittee);
  void SpriteDying(Sprite *pSprite);

  TTF_Font *_ttfFont;
  Mix_Music *_mmMusic;
  Mix_Chunk *_mcWhack;
  Mix_Chunk *_mcTaunt;
  Mix_Chunk *_mcBoo;
  Image *_pOfficeImage;
  Image *_pTargetImage;
  Image *_pPowImage;
  Image *_pGuyImages[5];
  Image *_pSmallGuyImage;
  Image *_pGameOverImage;
  Sprite *_pTargetSprite;
  Sprite *_pPowSprite;
  Sprite *_pGuySprites[5];
  int _iGuyDelay[5];
  int _iGuyMasterDelay;
  int _iHits;
  int _iMisses;
  bool _bGameOver;
};

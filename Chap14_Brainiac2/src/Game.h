#pragma once

#include <SDL.h>

#include <iostream>
#include <algorithm> 

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
  bool SpriteCollision(Sprite* pSpriteHitter,
			       Sprite* pSpriteHittee);  
  Bitmap*     _pTiles[9];
  bool        _bTileStates[4][4];
  int         _iTiles[4][4];
  SDL_Point   _ptTile1, _ptTile2;
  int         _iMatches, _iTries;
  Mix_Chunk*  _mcSelect;
  Mix_Chunk*  _mcMatch;
  Mix_Chunk*  _mcMisMatch;
  Mix_Chunk*  _mcWin;
};

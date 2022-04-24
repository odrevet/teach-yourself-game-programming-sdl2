#pragma once

#include <vector>
#include "Sprite.h"

typedef enum JOYSTATE_E
{
  JOY_NONE = (1 << 0),
  JOY_LEFT = (1 << 1),
  JOY_RIGHT = (1 << 2),
  JOY_UP = (1 << 3),
  JOY_DOWN = (1 << 4),
  JOY_FIRE1 = (1 << 5),
  JOY_FIRE2 = (1 << 6)
} JOYSTATE;

/** @interface IGame
    That interface must be implemented by any new games
*/

class IGame
{
public:
  virtual ~IGame() = 0;
  virtual bool Initialize() = 0;
  virtual void Start() = 0;
  virtual void End() = 0;
  virtual void Activate() = 0;
  virtual void Deactivate() = 0;
  virtual void Paint() = 0;
  virtual void Cycle() = 0;
  virtual void HandleKeys() = 0;
  virtual void MouseButtonDown(int x, int y, bool bLeft) = 0;
  virtual void MouseButtonUp(int x, int y, bool bLeft) = 0;
  virtual void MouseMove(int x, int y) = 0;
  virtual void HandleJoystick(JOYSTATE jsJoystickState) = 0;
  virtual bool SpriteCollision(Sprite *pSpriteHitter,
                               Sprite *pSpriteHittee) = 0;
  virtual void SpriteDying(Sprite *pSprite) = 0;
};

inline IGame::~IGame() {}

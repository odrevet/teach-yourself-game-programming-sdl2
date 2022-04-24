#pragma once

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
};

inline IGame::~IGame() {}

#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <iostream>

#include "IGame.h"
#include "GameEngine.h"

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

  SDL_Texture *icon;
  void DrawImage(SDL_Renderer *renderer, int x, int y);  
};

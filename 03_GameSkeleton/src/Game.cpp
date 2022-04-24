//-----------------------------------------------------------------
// Game Skeleton Application
// C++ Source - Skeleton.cpp
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Game.h"

//-----------------------------------------------------------------
// Game Engine Functions
//-----------------------------------------------------------------

Game::~Game()
{
}

bool Game::Initialize()
{
  // get the game engine
  GameEngine *pGameEngine = GameEngine::GetEngine();
  pGameEngine->SetFrameRate(15);

  // load the icon to draw on the screen
  SDL_Surface *icon_surface = IMG_Load("res/Skeleton.png");
  if (icon_surface == nullptr)
    std::cout << SDL_GetError() << std::endl;

  this->icon = SDL_CreateTextureFromSurface(pGameEngine->GetRenderer(),
                                            icon_surface);
  if (this->icon == nullptr)
    std::cout << SDL_GetError() << std::endl;
  SDL_FreeSurface(icon_surface);

  return true;
}

void Game::Start()
{
  // Seed the random number generator
  srand(SDL_GetTicks());
}

void Game::End()
{
  // Cleanup the game engine
  GameEngine *pGameEngine = GameEngine::GetEngine();
  delete pGameEngine;
}

void Game::Activate()
{
}

void Game::Deactivate()
{
}

void Game::Paint()
{
}

void Game::Cycle()
{
  GameEngine *pGameEngine = GameEngine::GetEngine();

  // Draw the skeleton icon at random positions on the game screen
  int x = rand() % pGameEngine->GetWidth();
  int y = rand() % pGameEngine->GetHeight();

  this->DrawImage(pGameEngine->GetRenderer(), x, y);
}

void Game::DrawImage(SDL_Renderer *renderer, int x, int y)
{
  int iW, iH;
  SDL_QueryTexture(this->icon, NULL, NULL, &iW, &iH);
  SDL_Rect rect = {x, y, iW, iH};

  int retcode = SDL_RenderCopy(renderer, this->icon, NULL, &rect);
  if (retcode < 0)
    std::cout << "ERR DRAW " << SDL_GetError() << std::endl;

  SDL_RenderPresent(renderer);
}

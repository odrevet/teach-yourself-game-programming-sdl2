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

  return true;
}

void Game::Start()
{
  // Seed the random number generator
  srand(SDL_GetTicks());

  GameEngine *pGE = GameEngine::GetEngine();

  // Set the position and size of the initial rectangle
  this->_rcRectangle.x = pGE->GetWidth() * 2 / 5;
  this->_rcRectangle.y = pGE->GetHeight() * 2 / 5;
  this->_rcRectangle.w = pGE->GetWidth() / 5;
  this->_rcRectangle.h = pGE->GetHeight() / 5;
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
  GameEngine *pGE = GameEngine::GetEngine();
  SDL_Renderer *renderer = pGE->GetRenderer();
  int width = pGE->GetWidth();
  int height = pGE->GetHeight();

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

  // Draw grid lines as a background for the rectangles
  const int iGridLines = 50;
  for (int i = 1; i <= iGridLines; i++)
  {
    // Draw a horizontal grid line
    SDL_RenderDrawLine(renderer,
                       0,
                       height * i / iGridLines,
                       width,
                       height * i / iGridLines);

    // Draw a vertical grid line
    SDL_RenderDrawLine(renderer,
                       width * i / iGridLines,
                       0,
                       width * i / iGridLines,
                       height);
  }
}

void Game::Cycle()
{
  GameEngine *pGE = GameEngine::GetEngine();
  SDL_Renderer *renderer = pGE->GetRenderer();

  // Randomly alter the position and size of the rectangle
  this->_rcRectangle.x += (rand() % 21) - 10;
  this->_rcRectangle.y += (rand() % 21) - 10;
  this->_rcRectangle.w += (rand() % 21) - 10;
  this->_rcRectangle.h += (rand() % 21) - 10;

  // Draw the new rectangle in a random color
  SDL_SetRenderDrawColor(renderer,
                         rand() % 256,
                         rand() % 256,
                         rand() % 256,
                         255);

  SDL_RenderFillRect(renderer, &this->_rcRectangle);
  SDL_RenderPresent(renderer);
}

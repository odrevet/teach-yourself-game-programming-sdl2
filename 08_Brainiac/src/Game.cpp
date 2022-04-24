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

  // Set the frame rate
  pGameEngine->SetFrameRate(1);

  // Initialize the joystick
  pGameEngine->InitJoystick();

  return true;
}

void Game::Start()
{
  // Seed the random number generator
  srand(SDL_GetTicks());

  GameEngine *pGE = GameEngine::GetEngine();
  SDL_Renderer *renderer = pGE->GetRenderer();

  // Create and load the tile bitmaps
  _pTiles[0] = new Bitmap(renderer, "res/TileBlank.bmp");
  _pTiles[1] = new Bitmap(renderer, "res/Tile1.bmp");
  _pTiles[2] = new Bitmap(renderer, "res/Tile2.bmp");
  _pTiles[3] = new Bitmap(renderer, "res/Tile3.bmp");
  _pTiles[4] = new Bitmap(renderer, "res/Tile4.bmp");
  _pTiles[5] = new Bitmap(renderer, "res/Tile5.bmp");
  _pTiles[6] = new Bitmap(renderer, "res/Tile6.bmp");
  _pTiles[7] = new Bitmap(renderer, "res/Tile7.bmp");
  _pTiles[8] = new Bitmap(renderer, "res/Tile8.bmp");

  // Clear the tile states and images
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
    {
      _bTileStates[i][j] = false;
      _iTiles[i][j] = 0;
    }

  // Initialize the tile images randomly
  for (int i = 0; i < 2; i++)
    for (int j = 1; j < 9; j++)
    {
      int x = rand() % 4;
      int y = rand() % 4;
      while (_iTiles[x][y] != 0)
      {
        x = rand() % 4;
        y = rand() % 4;
      }
      _iTiles[x][y] = j;
    }

  // Initialize the tile selections and match/try count
  _ptTile1.x = _ptTile1.y = -1;
  _ptTile2.x = _ptTile2.y = -1;
  _iMatches = _iTries = 0;
}

void Game::End()
{
  // Cleanup the tile bitmaps
  for (int i = 0; i < 9; i++)
    delete _pTiles[i];

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
  GameEngine *pGameEngine = GameEngine::GetEngine();
  SDL_Renderer *renderer = pGameEngine->GetRenderer();

  // Draw the tiles
  int iTileWidth = _pTiles[0]->GetWidth();
  int iTileHeight = _pTiles[0]->GetHeight();
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      if (_bTileStates[i][j] || ((i == _ptTile1.x) && (j == _ptTile1.y)) ||
          ((i == _ptTile2.x) && (j == _ptTile2.y)))
        _pTiles[_iTiles[i][j]]->Draw(renderer, i * iTileWidth, j * iTileHeight);
      else
        _pTiles[0]->Draw(renderer, i * iTileWidth, j * iTileHeight);

  SDL_RenderPresent(renderer);
}

void Game::Cycle()
{
}

void Game::HandleKeys()
{
  SDL_PumpEvents();
  const Uint8 *state = SDL_GetKeyboardState(NULL);

  // Q
  if (state[SDL_GetScancodeFromKey(SDLK_q)])
  {
    exit(0);
  }
}

void Game::MouseButtonDown(int x, int y, bool bLeft)
{
  GameEngine *pGE = GameEngine::GetEngine();
  SDL_Renderer *renderer = pGE->GetRenderer();

  // Determine which tile was clicked
  int iTileX = x / _pTiles[0]->GetWidth();
  int iTileY = y / _pTiles[0]->GetHeight();

  // Make sure the tile hasn't already been matched
  if (!_bTileStates[iTileX][iTileY])
  {
    // See if this is the first tile selected
    if (_ptTile1.x == -1)
    {
      // Set the first tile selection
      _ptTile1.x = iTileX;
      _ptTile1.y = iTileY;
    }
    else if ((iTileX != _ptTile1.x) || (iTileY != _ptTile1.y))
    {
      if (_ptTile2.x == -1)
      {
        // Increase the number of tries
        _iTries++;

        // Set the second tile selection
        _ptTile2.x = iTileX;
        _ptTile2.y = iTileY;

        // See if it's a match
        if (_iTiles[_ptTile1.x][_ptTile1.y] == _iTiles[_ptTile2.x][_ptTile2.y])
        {
          // Set the tile state to indicate the match
          _bTileStates[_ptTile1.x][_ptTile1.y] = true;
          _bTileStates[_ptTile2.x][_ptTile2.y] = true;

          // Clear the tile selections
          _ptTile1.x = _ptTile1.y = _ptTile2.x = _ptTile2.y = -1;

          // Update the match count and check for winner
          if (++_iMatches == 8)
          {
            char szText[64];
            sprintf(szText, "You won in %d tries.", _iTries);
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
                                     "Brainiac",
                                     szText,
                                     pGE->GetWindow());
          }
        }
      }
      else
      {
        // Clear the tile selections
        _ptTile1.x = _ptTile1.y = _ptTile2.x = _ptTile2.y = -1;
      }
    }

    // Force a repaint to update the tile
    SDL_RenderPresent(renderer);
  }
}

void Game::MouseButtonUp(int x, int y, bool bLeft)
{
}

void Game::MouseMove(int x, int y)
{
}

void Game::HandleJoystick(JOYSTATE jsJoystickState)
{
}

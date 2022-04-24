//-----------------------------------------------------------------
// Game Engine Object
// C++ Source - GameEngine.cpp
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "GameEngine.h"

//-----------------------------------------------------------------
// Static Variable Initialization
//-----------------------------------------------------------------
GameEngine *GameEngine::m_pGameEngine = NULL;

//-----------------------------------------------------------------
// GameEngine Constructor(s)/Destructor
//-----------------------------------------------------------------
GameEngine::GameEngine()
{
}

GameEngine::~GameEngine()
{
  Mix_Quit();
  IMG_Quit();
  SDL_Quit();
}

//-----------------------------------------------------------------
// Game Engine General Methods
//-----------------------------------------------------------------
bool GameEngine::Initialize(const char *szTitle, const char *szIcon, int iWidth, int iHeight)
{
  // Set the member variables for the game engine
  m_pGameEngine = this;
  m_hWindow = NULL;
  if (strlen(szTitle) > 0)
    strcpy(m_szTitle, szTitle);
  if (strlen(szTitle) > 0)
    strcpy(m_szIcon, szIcon);

  m_iWidth = iWidth;
  m_iHeight = iHeight;
  m_iFrameDelay = 50; // 20 FPS default
  m_bSleep = true;

  SDL_Init(SDL_INIT_VIDEO |
           SDL_INIT_AUDIO |
           SDL_INIT_GAMECONTROLLER); // Initialize SDL2

  // Initialize SDL2 Mixer
  if (Mix_OpenAudio(22050, AUDIO_U8, 2, 512) < 0)
  {
    std::cout << "Unable to init sound engine: " << SDL_GetError() << std::endl;
  }

  // Initialize SDL2 TTF
  if (TTF_Init() == -1)
  {
    std::cout << "TTF_Init: " << TTF_GetError() << std::endl;
    exit(EXIT_FAILURE);
  }

  // create the window
  m_hWindow = SDL_CreateWindow(m_szTitle,               // window title
                               SDL_WINDOWPOS_UNDEFINED, // initial x position
                               SDL_WINDOWPOS_UNDEFINED, // initial y position
                               m_iWidth,                // width, in pixels
                               m_iHeight,               // height, in pixels
                               SDL_RENDERER_ACCELERATED |
                                   SDL_RENDERER_PRESENTVSYNC // flags
  );
  if (!m_hWindow)
    return false;

  // set the window icon from the .ico file
  //  The icon is attached to the window pointer
  SDL_Surface *icone_surface = IMG_Load(szIcon);
  SDL_SetWindowIcon(m_hWindow, icone_surface);

  // the surface containing the icon pixel data is no longer required.
  SDL_FreeSurface(icone_surface);

  // Create a Renderer
  m_renderer = SDL_CreateRenderer(m_hWindow,
                                  0,
                                  SDL_RENDERER_ACCELERATED |
                                      SDL_RENDERER_PRESENTVSYNC);

  // Clear the screen
  SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
  SDL_RenderClear(m_renderer);
  SDL_RenderPresent(m_renderer);

  return true;
}

void GameEngine::Run()
{
  static int iTickTrigger = 0;
  int iTickCount;
  bool done = false;

  // start the game now
  this->SetSleep(false);
  m_game->Start();

  // Enter the main message loop
  while (!done)
  {
    // Make sure the game engine isn't sleeping
    if (!this->GetSleep())
    {
      // Check the tick count to see if a game cycle has elapsed
      iTickCount = SDL_GetTicks();
      if (iTickCount > iTickTrigger)
      {
        iTickTrigger = iTickCount + this->GetFrameDelay();
        m_game->Cycle();
        m_game->HandleKeys();
        this->CheckJoystick();
      }
    }

    this->HandleEvent();

    // Paint the game
    m_game->Paint();
  }

  // End the game
  m_game->End();
}

void GameEngine::HandleEvent()
{
  SDL_Event ev;
  while (SDL_PollEvent(&ev))
  {
    switch (ev.type)
    {
    case SDL_WINDOWEVENT:
      switch (ev.window.event)
      {
      case SDL_WINDOWEVENT_CLOSE:
        exit(EXIT_SUCCESS);
        break;
      }
    case SDL_MOUSEMOTION:
      m_game->MouseMove(ev.motion.x, ev.motion.y);
      break;
    case SDL_MOUSEBUTTONDOWN:
      m_game->MouseButtonDown(ev.button.x,
                              ev.button.y,
                              ev.button.button == SDL_BUTTON_LEFT ? true : false);
      break;
    case SDL_MOUSEBUTTONUP:
      m_game->MouseButtonUp(ev.button.x,
                            ev.button.y,
                            ev.button.button == SDL_BUTTON_LEFT ? true : false);
    case SDL_CONTROLLERDEVICEADDED:
      // this->CaptureJoystick( ev.cdevice.which );
      break;
    case SDL_CONTROLLERDEVICEREMOVED:
      this->ReleaseJoystick(ev.cdevice.which);
      break;
    }
  }
}

void GameEngine::ErrorQuit(char *szErrorMsg)
{
  SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                           "Critical Error",
                           szErrorMsg,
                           GetWindow());
}

bool GameEngine::InitJoystick()
{
  uint uiNumJoysticks;
  if ((uiNumJoysticks = SDL_NumJoysticks()) == 0)
    return false;

  // Make sure the joystick is attached
  m_gameController = SDL_GameControllerOpen(0);
  if (m_gameController == NULL)
    return false;

  // get the min and max axis values
  int min = std::numeric_limits<Sint16>::min();
  int max = std::numeric_limits<Sint16>::max();
  int center = (min + max) / 2;

  // calculate the trip values
  m_rcJoystickTrip.x = (min + center) / 2;
  m_rcJoystickTrip.y = (max + center) / 2;
  m_rcJoystickTrip.h = (min + center) / 2;
  m_rcJoystickTrip.w = (max + center) / 2;

  return true;
}

void GameEngine::CaptureJoystick(int id)
{
  if (SDL_IsGameController(id))
  {
    m_gameController = SDL_GameControllerOpen(id);
    if (m_gameController)
    {
#ifdef DEBUG
      const char *name = SDL_GameControllerName(m_gameController);
      std::cout << "Found a valid controller at index " << id
                << ", named: " << name << std::endl;
      delete name;
#endif
    }
    else
    {
      std::cout << "Error while capturing game controller " << SDL_GetError()
                << std::endl;
    }
  }
}

void GameEngine::ReleaseJoystick(int id)
{
  SDL_GameControllerClose(m_gameController);
}

void GameEngine::CheckJoystick()
{
  SDL_GameController *controller = this->GetController();
  int jsJoystickState = JOY_NONE;
  Sint16 axis = 0;

  // Check horizontal movement
  axis = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX);
  if (axis)
  {
    if (axis < m_rcJoystickTrip.x)
      jsJoystickState |= JOY_LEFT;
    else if (axis > m_rcJoystickTrip.w)
    {
      jsJoystickState |= JOY_RIGHT;
    }
  }

  // Check vertical movement
  axis = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY);
  if (axis)
  {
    if (axis < m_rcJoystickTrip.h)
      jsJoystickState |= JOY_UP;
    else if (axis > m_rcJoystickTrip.y)
    {
      jsJoystickState |= JOY_DOWN;
    }
  }

  // check joystick buttons
  Uint8 is_pressed_a = SDL_GameControllerGetButton(controller,
                                                   SDL_CONTROLLER_BUTTON_A);
  Uint8 is_pressed_b = SDL_GameControllerGetButton(controller,
                                                   SDL_CONTROLLER_BUTTON_B);
  if (is_pressed_a)
    jsJoystickState |= JOY_FIRE1;
  if (is_pressed_b)
    jsJoystickState |= JOY_FIRE2;

  // Allow the game to handle the joystick
  m_game->HandleJoystick((JOYSTATE)jsJoystickState);
}

// Sprite managmnent functions
void GameEngine::AddSprite(Sprite *pSprite)
{
  // Add a sprite to the sprite vector
  if (pSprite != NULL)
  {
    // See if there are sprites already in the sprite vector
    if (m_vSprites.size() > 0)
    {
      // Find a spot in the sprite vector to insert the sprite by its z-order
      vector<Sprite *>::iterator siSprite;
      for (siSprite = m_vSprites.begin(); siSprite != m_vSprites.end(); siSprite++)
        if (pSprite->GetZOrder() < (*siSprite)->GetZOrder())
        {
          // Insert the sprite into the sprite vector
          m_vSprites.insert(siSprite, pSprite);
          return;
        }
    }

    // The sprite's z-order is highest, so add it to the end of the vector
    m_vSprites.push_back(pSprite);
  }
}

void GameEngine::DrawSprites()
{
  // Draw the sprites in the sprite vector
  vector<Sprite *>::iterator siSprite;
  for (siSprite = m_vSprites.begin(); siSprite != m_vSprites.end(); siSprite++)
    (*siSprite)->Draw(this->m_renderer);
}

void GameEngine::UpdateSprites()
{
  // Update the sprites in the sprite vector
  SDL_Rect rcOldSpritePos;
  SPRITEACTION saSpriteAction;
  vector<Sprite *>::iterator siSprite;
  for (siSprite = m_vSprites.begin(); siSprite != m_vSprites.end(); siSprite++)
  {
    // Save the old sprite position in case we need to restore it
    rcOldSpritePos = (*siSprite)->GetPosition();

    // Update the sprite
    saSpriteAction = (*siSprite)->Update();

    // Handle the SA_KILL sprite action
    if (saSpriteAction & SA_KILL)
    {
      delete (*siSprite);
      m_vSprites.erase(siSprite);
      siSprite--;
      continue;
    }

    // See if the sprite collided with any others
    if (CheckSpriteCollision(*siSprite))
      // Restore the old sprite position
      (*siSprite)->SetPosition(rcOldSpritePos);
  }
}

void GameEngine::CleanupSprites()
{
  // Delete and remove the sprites in the sprite vector
  vector<Sprite *>::iterator siSprite;
  for (siSprite = m_vSprites.begin(); siSprite != m_vSprites.end(); siSprite++)
  {
    delete (*siSprite);
    m_vSprites.erase(siSprite);
    siSprite--;
  }
}

Sprite *GameEngine::IsPointInSprite(int x, int y)
{
  // See if the point is in a sprite in the sprite vector
  vector<Sprite *>::reverse_iterator siSprite;
  for (siSprite = m_vSprites.rbegin(); siSprite != m_vSprites.rend(); siSprite++)
    if (!(*siSprite)->IsHidden() && (*siSprite)->IsPointInside(x, y))
      return (*siSprite);

  // The point is not in a sprite
  return nullptr;
}

bool GameEngine::CheckSpriteCollision(Sprite *pTestSprite)
{
  // See if the sprite has collided with any other sprites
  vector<Sprite *>::iterator siSprite;
  for (siSprite = m_vSprites.begin(); siSprite != m_vSprites.end(); siSprite++)
  {
    // Make sure not to check for collision with itself
    if (pTestSprite == (*siSprite))
      continue;

    // Test the collision
    if (pTestSprite->TestCollision(*siSprite))
      // Collision detected
      return m_game->SpriteCollision((*siSprite), pTestSprite);
  }

  // No collision
  return false;
}

void GameEngine::PlaySong(Mix_Music *music, bool bRestart)
{
  int iTimes = 1;
  if (bRestart)
    iTimes = -1;

  if (Mix_PlayMusic(music, iTimes) == -1)
  {
    cout << "Mix_PlayMusic: " << Mix_GetError() << endl;
  }
}

void GameEngine::PauseSong()
{
  Mix_PauseMusic();
}

void GameEngine::ClosePlayer()
{
  Mix_HaltMusic();
}

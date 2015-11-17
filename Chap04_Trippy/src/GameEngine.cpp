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
GameEngine::GameEngine(){

}

GameEngine::~GameEngine()
{
}

//-----------------------------------------------------------------
// Game Engine General Methods
//-----------------------------------------------------------------
bool GameEngine::Initialize(const char* szTitle, const char* szIcon, int iWidth, int iHeight)
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
  m_iFrameDelay = 50;         // 20 FPS default
  m_bSleep = true;
  
  SDL_Init(SDL_INIT_VIDEO);   // Initialize SDL2

  //Initialize SDL2 TTF
  if(TTF_Init()==-1) {
    std::cout << "TTF_Init: " << TTF_GetError() << std::endl;
    exit(EXIT_FAILURE);
  }

  //create the window
  m_hWindow = SDL_CreateWindow(m_szTitle,                  // window title
			       SDL_WINDOWPOS_UNDEFINED,    // initial x position
			       SDL_WINDOWPOS_UNDEFINED,    // initial y position
			       m_iWidth,                   // width, in pixels
			       m_iHeight,                  // height, in pixels
			       0                           // flags
			       );
  if (!m_hWindow)
    return false;
  
  //set the window icon from the .ico file
  // The icon is attached to the window pointer
  SDL_Surface *icone_surface = IMG_Load(szIcon);
  SDL_SetWindowIcon(m_hWindow, icone_surface);
  
  //the surface containing the icon pixel data is no longer required.
  SDL_FreeSurface(icone_surface);
  
  //Create a Renderer
  m_renderer = SDL_CreateRenderer(m_hWindow,     //window
				  0,
				  0);             //flags

  //Clear the screen
  SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
  SDL_RenderClear(m_renderer);
  SDL_RenderPresent(m_renderer);
  
  return true;
}

void GameEngine::HandleEvent()
{
    SDL_Event ev;
    while ( SDL_PollEvent(&ev) ) {
      switch(ev.type) {
      case SDL_WINDOWEVENT:
	switch ( ev.window.event ){
	case SDL_WINDOWEVENT_CLOSE: 
	  exit(EXIT_SUCCESS);
	  break;
	}
      case SDL_KEYUP:
	if ( ev.key.keysym.sym == SDLK_q ) {
	  exit(EXIT_SUCCESS);
	}
	break;
      }
    }
}

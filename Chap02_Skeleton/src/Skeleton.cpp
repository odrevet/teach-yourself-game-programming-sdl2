//-----------------------------------------------------------------
// Skeleton Application
// C++ Source - Skeleton.cpp
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Skeleton.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

//-----------------------------------------------------------------
// Global Functions
//-----------------------------------------------------------------

// "Draw" text to a texture (do not actually draw on the renderer)
SDL_Texture *DrawText(SDL_Renderer *renderer, const char* text, TTF_Font *Font, SDL_Color FontColor){
  SDL_Surface* text_surface = TTF_RenderText_Blended(Font,
						     text,
						     FontColor);

  if(!text_surface){
    std::cout << "TTF_RenderText: " << TTF_GetError() << std::endl;
  }
    
  SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer,
							   text_surface);
  SDL_FreeSurface(text_surface);

  return text_texture;
}


//main function
int main(int argc, char *argv[])
{
  bool done = false;
  static char szAppName[] = "Skeleton";

  // Create the window class for the main window
  SDL_Window *window;                    // Declare a Window pointer

  SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2

  //Initialize SDL2 TTF
  if(TTF_Init()==-1) {
    std::cout << "TTF_Init: " << TTF_GetError() << std::endl;
    exit(EXIT_FAILURE);
  }

  // Create an application window with the following settings:
  window = SDL_CreateWindow(
			    szAppName,                      // window title
			    SDL_WINDOWPOS_UNDEFINED,        // initial x position
			    SDL_WINDOWPOS_UNDEFINED,        // initial y position
			    SCREEN_WIDTH,                   // width, in pixels
			    SCREEN_HEIGHT,                  // height, in pixels
			    0                               // flags
			    );

  // Check that the window was successfully created
  if (window == NULL) {
    // In the case that the window could not be made...
    printf("Could not create window: %s\n", SDL_GetError());
    return 1;
  }

  //set the window icon from the .ico file
  // The icon is attached to the window pointer
  SDL_Surface *icone_surface = IMG_Load("res/Skeleton_sm.ico");
  
  SDL_SetWindowIcon(window, icone_surface);

  // ...and the surface containing the icon pixel data is no longer required.
  SDL_FreeSurface(icone_surface);
  

  //Create a Renderer
  SDL_Renderer* renderer = SDL_CreateRenderer(window,
					      0,
					      SDL_RENDERER_ACCELERATED |
					      SDL_RENDERER_PRESENTVSYNC);  
  
  //init text
  TTF_Font* Font = TTF_OpenFont("res/DejaVuSans.ttf", 12);
  if ( Font == nullptr ){
    std::cout << " Failed to load font : " << TTF_GetError() << std::endl;
    return false;
  }

  SDL_Color FontColor = {0, 0, 0};
  SDL_Texture *text_texture = DrawText(renderer,
				       "This is a skeleton application! ",
				       Font,
				       FontColor);

  //Get the text texture w/h so we can center it on the screen
  int iW, iH;
  SDL_QueryTexture(text_texture, NULL, NULL, &iW, &iH);
  int x = SCREEN_WIDTH / 2 - iW / 2;
  int y = SCREEN_HEIGHT / 2 - iH / 2;
  SDL_Rect Message_rect = {x, y, iW, iH};

  
  // Enter the main loop
  while (!done) {
    SDL_Event ev;
    while ( SDL_PollEvent(&ev) ) {
      switch(ev.type) {
      case SDL_WINDOWEVENT:
	if ( ev.window.event == SDL_WINDOWEVENT_CLOSE ) {
	  done = true;
	}
	break;
      case SDL_KEYUP:
	if ( ev.key.keysym.sym == SDLK_q ) {
	  done = true;
	}
	break;
      }
    }

    //Clear the background 
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    
    //Draw text
    SDL_RenderCopy(renderer, text_texture, NULL, &Message_rect);

    //render
    SDL_RenderPresent(renderer);
  }

  // Exit the application
  SDL_DestroyTexture(text_texture);
  SDL_DestroyWindow(window);
  TTF_CloseFont(Font);
  SDL_Quit();
  
  return 0;
}

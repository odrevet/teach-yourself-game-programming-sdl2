In this chapter a simple window is opened with a white background and a black
text saying "this is a skeleton application" which beside the window icon behine
a skeleton icon is an obvious pune as this code will be the skeleton of the
next chapters.

The reader can see immediatly how easy it is to create a window with SDL2
instead of using the WIN32 API as there is no complex messaging system and
the parameters of the window creation function are self explanatory.

The only complicated thing is the use of the SDL2 TTF library as there is no
WIN32 "DrawText" equivalent with SDL2.

Due to the uses of SDL2_ttf and SDL2_image the code is a bit longer than the WIN32 version
but the advantages of SDL2 are obvious.


# Key differences with the original code

* Uses Makefile
* Uses of SDL2 for the window creation and event listening
* Uses of SDL2_TTF for the text display
* Uses of SDL2_Image for the window icon

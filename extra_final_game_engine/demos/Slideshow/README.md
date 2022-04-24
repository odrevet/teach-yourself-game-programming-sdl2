# Key differances with the original code
* The Image Class is powered by SDL_Image and can load several image type
* In the Image Class, removed some constructors and the Create functions
* Image are always loaded from a filename, never from ressources or created with a color
* The Image filename in the constructor is const since there are no more implicite conversion in C++11
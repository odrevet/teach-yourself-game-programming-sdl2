# Key differances with the original code
* The Bitmap Class is powered by SDL_Image and can load several image type
* In the Bitmap Class, removed some constructors and the Create functions
* Bitmap are always loaded from a filename, never from ressources or created with a color
* The Bitmap filename in the constructor is const since there are no more implicite conversion in C++11
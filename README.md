This is an SDL2 rewrite of the examples founds in "Teach Yourself Game Programming in 24 Hours" by <i>Michael Morrison</i>.
ISBN 067232461X, 9780672324611
Google Books : https://books.google.fr/books/about/Sams_Teach_Yourself_Game_Programming_in.html?id=Ymt93N7FJ5wC

Full modifications are:

* Uses SDL2 (removed all WIN32 API calls and RC files)
* Uses GCC (g++ with C11) and Make (removed all Visual Studio project files)
* Can be build under Linux or Windows with MinGW
* Moved source files into a "src" folder and images/sounds into a "res" folder
* Created a Game Class for each game specific code
* Removed build objects and binaries
* in every games press 'q' to quit
* See README.md in each folder for detailed comments about each game changes

Thanks to "Michael Morrison" for this very well written and usefull book which
I hope this new "SDL2" rewrite will enchance the reader experiance, as
the SDL2 is portable and the API is increadibly concise.

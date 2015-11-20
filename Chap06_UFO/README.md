In this example a flying saucer glide above a desertic background image
The UFO can be controled with the keyboard, a left click teleport the UFO
on the click location and a right click stops the UFO.
This chapter also introduce transparency color. 

#Key differances with the original code
* The transparency is set in Bitmap constructor instead of Bitmap::Draw
* In the original code the transparancy is set with a bTrans Boolean and a
  Transparancy color. In this new version only the transparancy color is required.
  No transparency if the transparancy color is NULL
* The alpha value can be set (4th csTransColor member)
* When build with DEBUG (make DEBUG=yes) the speed and key down in print on standard output

# TODO
* Keyboard and mouse input
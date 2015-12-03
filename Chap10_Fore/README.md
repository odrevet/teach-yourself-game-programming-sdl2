#In this chapter a Sprite class is created, which hold an image, a velocity,
a coordinate and a bound limit (a rectangle) . When the bound limit is reach
a BOUNDACTION is triggered: 
*BOUNCE: the sprite velocity are reversed so it bounce.
*WRAP: the sprite appear at the other side of the bound area.
*STOP: the sprite stops.

Three golfball sprites are created, each with a bound differant BOUNDACTION.
Each golf ball sprite can be drag and drop with the mouse.

There are no collision detection between the sprites in this chapter. 

#About BOUNDACTIONS
the bound action are triggerd in the GameEngine part. In my opinion this is
a design flaw as the GameEngine is supposed to be opaque to the game developer,
thus the game developer is now limited to what bound action is present in the
game engine.
Bound action should have been exposed via a function pointer, with the function
in the game part and eventally the wrap, bounce and stop actions in the game
engine for convinience. 
The advantage is that the code is really simple, which is what the author was
seeking when writing the code and the book. 


#About the rewrite from WIN32 API's RECT to SDL2's SDL_Rect

The WIN32 API define the RECT struct with the fields: 

left

    The x-coordinate of the upper-left corner of the rectangle.
top

    The y-coordinate of the upper-left corner of the rectangle.
right

    The x-coordinate of the lower-right corner of the rectangle.
bottom

    The y-coordinate of the lower-right corner of the rectangle.


and SDL2 define a SDL_Rect with the fields: 

x
    The x location of the rectangle's upper left corner

y
    The y location of the rectangle's upper left corner

w
    The width of the rectangle

h
    The height of the rectangle


#Key differences with the origial code
*Removed unused variable ptBoundsSize in Sprite::Update
*Updated algorithm with SDL_Rect
*in DEBUG mode, the sprite draw his bound rect and his position
*in DEBUG mode, drag informations are printed on the standard output
*The srand is initialized with the time instead of the ticks
*The Sprite::IsPointInside has been rewrited, there do is a SDL_PointInRect
 function but it is only available in SDL>=2.0.4 which is yet not widly
 distributed in linux distros. 
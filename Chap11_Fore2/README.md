In this chapter a sprite manager is added as a vector of Sprite* and several
sprite related functions in the GameEngine class. 

Sprite can now be aware of each other and have a collide behaviour via the
SpriteCollision function in the Game class. 

The offset buffer is managed internally by SDL2 with the renderer flag
SDL_RENDERER_ACCELERATED. 
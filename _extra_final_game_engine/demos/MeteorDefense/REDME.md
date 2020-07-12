In this chapter a clone of missile command is created.


The sprites can now be set to be erased after a single animation (m_bOneCycle)
or on demande with the Sprite::Kill function. With this new GameEngine
functionallity the missiles and the asteroids can show an explosion when they
collides.

One big modification over the original code is in the GameEngine::UpdateSprites
function.

If the Game::SpriteDying adds a Sprite (for example, an explosion sprite), The
AddSprite function pushs a Sprite* in the m_vSprites vector, so the iterator
used in GameEngine::Update is invalidated, and a segmentation fault occures.

This problem did not occures when I played with the compiled executable from
the original version. So I assume that the compilateur used by the author did
not invalidate the iterators and internally managed the memory.

In this new version, a GameEngine::m_vSpritesToAdd vector is created, the
sprites to be added are pushed into this vector. After that all the sprites are
updates the m_vSpritesToAdd is merged with m_vSprites. 

With that said, the C++ standard tells that the insert invalidats the iterator.
It's always better to have a code that match as close as possible the standard so
it has a better chance to run on differant compilator.

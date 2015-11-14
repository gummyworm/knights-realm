# knights-realm
Knight's Realm was my first stab at a game engine.  Its life began toward the end of 2010 and ended in the middle of April 2011.  Although it is a functional engine, it has never been tested with a project of any reasonable scale and is surely full of bugs.  This is for archival purposes only.

Knight's Realm is a 2D engine.  Its design was influenced by Ogre3D (in the sense that nodes comprise the layout of the scene with the actual subjects to be rendered attached to these nodes).

The scripting was influenced by Panda3D.  Most of the engine is exposed to Python via a swig wrapper, and games built atop this engine were intended to be written in Python. Scenes are built and setup in Python, then any desired callbacks are registered.  At this point control is passed to the engine.  Until a callback is triggered the engine takes care of rendering, collision detection, etc.

To make scripting as simple as possible, most of the game state is stored within string-keyed maps.  Inter-entity messages (or "events") are also communicated using the names of the concerned entities. 

Map data is stored as XML and is compatible with the popular "Tiled" map-editor.  Spritesheets and sprite animations are also stored as XML.  Animations are represented as a range of spritesheet frames and a speed at which to play them back.  Depending on how the animation is started by the engine, these can be played back "one-shot" or looped.  

Sprites' collision bounds are represented as rotated quads with collision handled with a method based on the Separating Axis Theorem.  Python functions can be registered as callbacks upon collision.


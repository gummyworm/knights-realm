# knights-realm
Knight's Realm was my first stab at a game engine.  Its life began toward the end of 2010 and ended in the middle of April 2011.  
Although it is a functional engine, it has never been tested with a project of any reasonable scale and is surely full of bugs.  This is for archival purposes only.

Knight's Realm is a 2D engine.  Its design was influenced by Ogre3D (in the sense that nodes comprise the layout of the scene with the actual subjects to be rendered attached to these nodes).

The scripting was influenced by Panda3D.  Most of the engine is exposed to Python via a swig wrapper, and games built atop this engine were intended to be written in Python. Scenes are built and setup in Python, then any desired callbacks are registered.  At this point control is passed to the engine.  Until a callback is triggered the engine takes care of rendering, collision detection, etc.

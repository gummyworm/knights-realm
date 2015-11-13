%module engine
%{
#define SWIG_FILE_WITH_INIT
#include "game.h"

#include "entity.h"
#include "sprite.h"
#include "player.h"
#include "rect.h"
#include "frame.h"
#include "map.h"
#include "texture.h"
#include "text.h"

%}

%include stl.i

%include game.h
%include entity.h
%include sprite.h
%include player.h
%include rect.h
%include frame.h
%include map.h
%include texture.h
%include text.h


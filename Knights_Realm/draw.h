#ifndef _DRAW_H
#define _DRAW_H

#define TEXT_CHAR_SPACING 10
#define TEXT_LINE_SPACING 5
#define TEXT_X_MARGIN 5
#define TEXT_Y_MARGIN 5

#include <string>
#include "SDL_opengl.h"
#include "rect.h"

// forward declarations to avoid circular dependency.. feelsbadman...
class RectAlpha;
class RectTextured;

void DrawRectAlpha(RectAlpha* r);
void DrawRectTextured(RectTextured* r);
void DrawText(std::string text);
#endif
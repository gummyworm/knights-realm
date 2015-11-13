#ifndef _TEXTURE_H
#define _TEXTURE_H

#include <string>
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_opengl.h"

/* creates a GL texture from the image of the passed filename and returns its ID 
*/
GLuint LoadTexture(std::string texName);
GLuint SurfaceToTexture(SDL_Surface *surface, std::string = "");

#endif

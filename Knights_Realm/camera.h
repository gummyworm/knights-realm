#ifndef _CAMERA_H
#define _CAMERA_H

#include "SDL_opengl.h"

class Camera {
	// coordinates represent upper left hand point
	int x, y, z;

public:
	Camera() {x=0; y=0; z=0;}

	void Look();
	void SetPos(int X, int Y, int Z);

	void SetX(int X) {x=X;}
	void Sety(int Y) {y=Y;}
	void SetZ(int Z) {z=Z;}
	int GetX() {return x;}
	int GetY() {return y;}
	int GetZ() {return z;}
};

#endif

#ifndef _KRUTIL_H
#define _KRUTIL_H

#include <cmath>

#define PI 3.141592654

int DistFrom(int a, int b);
float DistFrom(float a, float b);

class Vector2 {
public:
	float x, y;
	Vector2() {}
	Vector2(float X, float Y) {x=X; y=Y;}

	void Sub(float X, float Y) {x-=X; y-=Y;}
	void Sub(Vector2* v) {x-=v->x, y-=v->y;}
	void Add(float X, float Y) {x+=X; y+=Y;}
	void Add(Vector2* v) {x+=v->x; y+=v->y;}
};

#endif
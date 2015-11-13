#ifndef _VECTOR_H
#define _VECTOR_H

#include <cmath>

class Vector2 {
	public:
		float x, y;
		Vector2(float X, float Y) {x=X; y=Y;}

		float Dot(float X, float Y) {return x*X + y*Y;}
		void Normalize() {x=x/sqrt(x*x+y*y); y=y/sqrt(x*x+y*y);}
};

#endif
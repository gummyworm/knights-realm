#include "krutil.h"

int DistFrom(int a, int b)
{
	if(a > b) {
		return abs(a - b);
	}
	else {
		return abs(b - a);
	}
}

float DistFrom(float a, float b)
{
	if(a > b) {
		return abs(a - b);
	}
	else {
		return abs(b - a);
	}
}

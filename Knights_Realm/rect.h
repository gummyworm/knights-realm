#ifndef _RECT_H
#define _RECT_H 

#include "SDL_opengl.h"
#include "draw.h"
#include "entity.h"

class RectAlpha : public Entity {
protected:
	int w, h;
	int xScale, yScale;
	GLfloat colorR, colorG, colorB, colorA;
public:
	RectAlpha();
	void Draw();
	int GetW() {return w;}
	int GetH() {return h;}
	int GetXScale() {return xScale;}
	int GetYScale() {return yScale;}
	GLfloat GetColorR() {return colorR;}
	GLfloat GetColorG() {return colorG;}
	GLfloat GetColorB() {return colorB;}
	GLfloat GetColorA() {return colorA;}

	void SetW(int W) {w=W;}
	void SetH(int H) {h=H;}
	void setXScale(int XS) {xScale=XS;}
	void SetYScale(int YS) {yScale=YS;}
};

class RectTextured : public RectAlpha {
protected:
	GLuint texture;
	GLfloat clipX, clipY, clipW, clipH;
public:
	RectTextured(int W=32, int H=32, GLuint tex=0, float cX=0.0, float cY=0.0, float cW=1.0, float cH=1.0, float cR=1.0, float cG=1.0, float cB=1.0, float cA=1.0);

	// draw the rectangle at the current translation (does not take x or y into account)
	void Draw();
	void FindClip(int frame, int texW, int texH, int tileW, int tileH);

	GLfloat GetClipX() {return clipX;}
	GLfloat GetClipY() {return clipY;}
	GLfloat GetClipW() {return clipW;}
	GLfloat GetClipH() {return clipH;}
	GLuint GetTexture() {return texture;}

	void SetTexture(GLuint tex) {texture=tex;}
};

#endif
#include "rect.h"
#include <iostream>

RectAlpha::RectAlpha() : Entity()
{
}

void RectAlpha::Draw()
{
	// TODO: use draw functions... or at least add rotation
    glColor4f(colorR, colorG, colorB, colorA);
    glPushMatrix();
    glBegin(GL_QUADS);
        glVertex2i(0, 0);
        glVertex2i(w, 0);
        glVertex2i(w, h);
        glVertex2i(0, h);
    glEnd();
    glPopMatrix();
}

RectTextured::RectTextured(int W, int H, GLuint tex, float cX, float cY, float cW, float cH, float cR, float cG, float cB, float cA) : RectAlpha()
{
    w=W; 
    h=H;
    texture=tex;
    colorR=cR;
    colorG=cG;
    colorB=cB;
    colorA=cA;

	clipX=cX;
	clipY=cY;
	clipW=cW;
	clipH=cH;
}

void RectTextured::Draw()
{
	DrawRectTextured(this);
    //glPushMatrix();
    //glTranslatef(0.0, 0.0, z);

    //glColor4f(colorR, colorG, colorB, colorA);
    //glBindTexture(GL_TEXTURE_2D, texture);
    //glEnable(GL_TEXTURE_2D);

    // TODO: sketch. Why doesn't it work without this test. Not entirely alpha texture?
    //glAlphaFunc(GL_GREATER, 0.1);
    //glEnable(GL_ALPHA_TEST);
    //    
    //glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    //glBegin(GL_QUADS);
    //    glTexCoord2f(clipX, clipY);
    //    glVertex2i(x, y);

    //    glTexCoord2f(clipX+clipW, clipY);
    //    glVertex2i(x+w, y);

    //    glTexCoord2f(clipX+clipW, clipY+clipH);
    //    glVertex2i(x+w, y+h);

    //    glTexCoord2f(clipX, clipY+clipH);
    //    glVertex2i(x, y+h);
    //glEnd();
    //glPopMatrix();
}

void RectTextured::FindClip(int frame, int texW, int texH, int tileW, int tileH)
{
    clipX=tileW * GLfloat(frame%(texW/tileW))/texW;
    clipY=tileH * GLfloat(frame/(texW/tileW))/texH;
    clipW=GLfloat(tileW)/GLfloat(texW);
    clipH=GLfloat(tileH)/GLfloat(texH);
}
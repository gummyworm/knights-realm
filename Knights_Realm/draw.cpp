#include "draw.h"

void DrawRectAlpha(int x, int y, int w, int h, GLfloat cR, GLfloat cG, GLfloat cB, GLfloat cA)
{
    glColor4f(cR, cG, cB, cA);
    glPushMatrix();
    glBegin(GL_QUADS);
        glVertex2i(x, y);
        glVertex2i(x+w, y);
        glVertex2i(x+w, y+h);
        glVertex2i(x, y+h);
    glEnd();
    glPopMatrix();
}

void DrawRectAlpha(RectAlpha* r)
{
	GLfloat cR=r->GetColorR();
	GLfloat cG=r->GetColorG();
	GLfloat cB=r->GetColorB();
	GLfloat cA=r->GetColorA();
	int w=r->GetW();
	int h=r->GetH();

    glPushMatrix();
    glColor4f(cR, cG, cB, cA);
    glBegin(GL_QUADS);
        glVertex2f(0.0, h);
        glVertex2f(w, h);
        glVertex2f(w, h);
        glVertex2f(0.0, h);
    glEnd();
    glPopMatrix();
}

void DrawRectTextured(RectTextured* r) 
{
	int w=r->GetW();
	int h=r->GetH();
	GLuint texture=r->GetTexture();
	GLfloat clipX=r->GetClipX();
	GLfloat clipY=r->GetClipY();
	GLfloat clipW=r->GetClipW();
	GLfloat clipH=r->GetClipH();

    glPushMatrix();

    //glColor4f(colorR, colorG, colorB, colorA);
    glBindTexture(GL_TEXTURE_2D, texture);
    glEnable(GL_TEXTURE_2D);

    // TODO: sketch. Why doesn't it work without this test. Not entirely alpha texture?
    glAlphaFunc(GL_GREATER, 0.1f);
    glEnable(GL_ALPHA_TEST);
        
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
        glTexCoord2f(clipX, clipY);
        glVertex2i(0, 0);

        glTexCoord2f(clipX+clipW, clipY);
        glVertex2i(w, 0);

        glTexCoord2f(clipX+clipW, clipY+clipH);
        glVertex2i(w, h);

        glTexCoord2f(clipX, clipY+clipH);
        glVertex2i(0, h);
    glEnd();
    glPopMatrix();
}
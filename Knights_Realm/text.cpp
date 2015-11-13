#include "text.h"

Text::Text() : Entity()
{
	fontW=512; 
	fontH=512; 
	charW=32; 
	charH=32; 
	charSpacing=0; 
	lineSpacing=0; 
	xMargin=0; 
	yMargin=0; 
	start=0; 
	w=500; 
	h=500; 
}
        
Text::Text(GLuint tex, std::string font) : Entity()
{
	font=tex; 
	font=LoadTexture(font); 
	start=0; 
}

void Text::Draw()
{
    int i;
    int cols=0, rows=0;
    GLfloat tx, ty, tw, th;

    tw=GLfloat(charW)/GLfloat(fontW);
    th=GLfloat(charH)/GLfloat(fontH);

    glPushMatrix();

    // # of chars to print before proceeding to a new column/row
    int colStop=(w-xMargin)/(charW+charSpacing);
    int rowStop=(h-yMargin)/(charH+lineSpacing);

    glColor4f(1.0, 1.0, 1.0, 1.0);
    glBindTexture(GL_TEXTURE_2D, font);
    glEnable(GL_TEXTURE_2D);
    for(i=start; i<text.size(); i++) {
        tx=charW * GLfloat(text[i]%(fontW/charW))/fontW;
        ty=charH * GLfloat(text[i]/(fontH/charH))/fontH;
        glBegin(GL_QUADS);
            glTexCoord2f(tx, ty);
            glVertex2i(0, 0);

            glTexCoord2f(tx+tw, ty);
            glVertex2i(charW, 0);

            glTexCoord2f(tx+tw, ty+th);
            glVertex2i(charW, charH);

            glTexCoord2f(tx, ty+th);
            glVertex2i(0, charH);
        glEnd();
        if(cols+1 >= colStop) {
            // go back to the start of the line, down a line
            glTranslatef(-cols*charW, charH, 0.0);
            cols=0;
            rows++;
            if(rows >= rowStop) {
                start=i;
                return;     // if all text is displayed, stop
            }
        }
        else {
            glTranslatef(charSpacing+charW, 0.0, 0.0);
            cols++;
        }
    }
    glPopMatrix();
}

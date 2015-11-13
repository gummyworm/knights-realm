#include "camera.h"

void Camera::Look() 
{
    glLoadIdentity();
    glTranslatef((GLfloat)x, (GLfloat)y, (GLfloat)z);
}

void Camera::SetPos(int X, int Y, int Z) 
{
    x=X;
    y=Y;
    z=Z;
}


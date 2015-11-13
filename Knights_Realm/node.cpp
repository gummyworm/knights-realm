#include "node.h"


Node::Node(float X, float Y, float Z, float R) : Entity()
{
	x=X;
	y=Y;
	z=Z;
	rot=R;
	dr=0.0;
	
	dX=0.0;
	dY=0.0;

	// TODO: not sure if want....
	children.clear();
}

void Node::Update() {
	// update the rotation
	if (dr != 0.0) {
		if(abs(dr) > DistFrom(rot, turnDst)) {
			rot=turnDst;
			dr=0.0f;
		}
		else {
			rot += dr;
		}
	}

    // update position
	if(dX != 0) {
		x=(x+dX * cos(rot*PI / 180.0));
		y=(y+dX * sin(rot*PI / 180.0));
		// TODO: straffe code here
	}
	if(dY != 0) {
		x=(x+dY * sin(rot * PI / 180.0)); 
		y=(y+dY * -cos(rot * PI / 180.0));
	}

	// update the children
	if(!children.empty()) {
		for(GameEntity::iterator it = children.begin(); it != children.end(); it++) {
			(*it)->Update();
		}
	}
}

void Node::Draw() {
	glPushMatrix();
	glTranslatef(x, y, z);
	glTranslatef(16, 16, 0);			// TODO: :'( no way of knowing how to get to the center of the object to draw... 
	glRotatef(rot, 0.0, 0.0, 1.0);
	glTranslatef(-16, -16, 0);			// TODO: same... should not use hardcoded w/2 and h/2 values.

	for(GameEntity::iterator it = children.begin(); it != children.end(); it++) {
		(*it)->Draw();
	}
	glPopMatrix();
}
	
void Node::Face(float dstX, float dstY)
{
	turnDst= atan2(dstY-y, dstX-x) * 180.0 / PI;
	if(turnDst < 0) {
		turnDst += 360.0;
	}
	if(turnDst > rot) {
		dr=turnSpeed;
	}
	else if(turnDst < rot) {
		dr=-turnSpeed;
	}
	else {
		dr=0.0;
	}
	turnDst += 90.0;	// rotate 90 more degrees so that the sprite is actually facing the point
}

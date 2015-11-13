#include "collision.h"

inline void RotateVector2Clockwise(Vector2 *v, float angle)
{
	float t;
	float cosa=cos(angle);
	float sina=sin(angle);
	t=v->x;
	v->x=t*cosa + v->y*sina;
	v->y=-t*sina + v->y*cosa;
}

bool ColRect::Check(ColRect* other)
{
	//std::cout<<"detecting collision between:  (x="<<parent->GetX()<<",y="<<parent->GetY()<<",w="<<w<<",h="<<h<<",theta="<<parent->GetRot()<<")  and  ";
	//std::cout<<"(x="<<other->parent->GetX()<<",y="<<other->parent->GetY()<<",w="<<other->w<<",h="<<other->h<<",theta="<<other->parent->GetRot()<<")"<<std::endl;

	Vector2 A, B;	// vertices of other
	Vector2 C;		// center of other
	Vector2 BL, TR;	// bottom-left and top-right of the other

	float angle=parent->GetRot() - other->parent->GetRot();	// orientation of rotated rect
	float cosa=cos(angle);		// precalculated trig.
	float sina=sin(angle);		// yep.

	float t, x, a;				// temporary variables
	float dX;					// deltaX for linear equations
	float ext1, ext2;			// min/max vertical values.

	// move other to make this rectangle cannonic
	C=other->parent->GetCenter();
	C.Sub(&parent->GetCenter());

	// rotate other clockwise by other->rot to make other axis angled
	RotateVector2Clockwise(&C, other->parent->GetRot());

	// calculate vertices of (translated and axis-aligned) other
	BL=TR=C;
	BL.Sub(&other->GetSize());
	TR.Add(&other->GetSize());

	// calculate vertices of (rotated) colRect
	A.x=-this->GetH()*sina; 
	B.x=A.x;
	t=this->GetW()*cosa; 
	A.x += t;
	B.x -= t;

	A.y=this->GetH()*cosa;
	B.y=A.y;
	t=this->GetW()*sina;
	A.y += t;
	B.y -= t;

	t=sina*cosa;

	// verify that A is vertical min/max, B is horizontal min/max
	if(t < 0) {
		t=A.x;
		A.x=B.x;
		B.x=t;
	
		t=A.y;
		A.y=B.y;
		B.y=t;
	}

	// verify that B is horizontal minimum (leftmost vertex)
	if(sina < 0) {
		B.x=-B.x;
		B.y=-B.y;
	}

	// if other (translated and axis aligned) isn't in the horizontal range of 
	// colliding with this (rotated), collision is impossible.
	if(B.x > TR.x || B.x > -BL.x) {
		return false;
	}

	// if this (rotated) is axis aligned, vertical min/max are easy to get
	if(t == 0) {
		ext1=A.y;
		ext2=-ext1;
	}

	// else, find vertical min/max in the range [BL.x, TR.x]
	else {
		x=BL.x-A.x;
		a=TR.x-A.x;

		// if the first vertical min/max isn't in (BL.x, TR.x), then 
		// find the vertical min/max on BL.x or on TR.x
		if(a*x > 0) {
			dX=A.x;
			if(x < 0) {dX -= B.x; ext1 -= B.y; x=a;}
			else {dX += B.x; ext1 += B.y;}
			ext1 *= x;
			ext1 /= dX;
			ext1 += A.y;
		}

		x=BL.x+A.x;
		a=TR.x+A.x;
		ext2=-A.y;
		
		// if the second vertical min/max isn't in (BL.x, TR.x), then
		// find the local vertical min/max on BL.x or on TR.x
		if(a*x > 0) {
			dX=-A.x;
			if(x < 0) {dX -= B.x; ext2 -= B.y; x=a;}
			else {dX += B.x; ext2 += B.y;}
			ext2 *= x;
			ext2 /= dX;
			ext2 -= A.y;
		}
	}
		
	// check whether other (translated and axis-aligned) is in the vertical range of colliding with this
	// (for the horizontal range of other)
	return !((ext1 < BL.y && ext2 < BL.y) ||
		(ext1 > TR.y && ext2 > TR.y));
}

void ColTraverser::Traverse(EvtMgr* evtMgr)
{
	// TODO: very inefficient means of checking (check all nodes against all other nodes)
	for(std::set<ColRect*>::iterator it=nodes.begin(); it != nodes.end(); it++) {		// TODO: <ColNode*>
		for(std::set<ColRect*>::iterator jt=nodes.begin(); jt != nodes.end(); jt++) {	// TODO: <ColNode*>
			if((*it) == (*jt)) continue;	// exclude testing collision against self
			if((*it)->Check((*jt)) == true) {
				evtMgr->Send((*it)->GetName()+"-into-"+(*jt)->GetName());
			}
		}
	}
}
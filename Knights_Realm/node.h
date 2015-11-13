#ifndef _NODE_H
#define _NODE_H

#include <iostream>
#include <set>
#include "SDL_opengl.h"
#include "krutil.h"
#include "entity.h"

class Node : public Entity {
private:
	/** the x, y, and z coordinates of the node.
	* these are used to position all children of the node.  Once attached to the node, all children are repositioned to this point in the Update
	* function.
	*/
	float x, y, z;

	/** the values to add to x and y each frame.
	* these values are added to the x and y coordinates during the update function
	*/
	float dX, dY;

	/** the rotation value of the node.
	* all children of this node will be rotated by this amount on the z-axis before rendering.
	*/
	float rot;

	/** the amount to be added to the current rotation.
	* the value added to rot every frame until rot == turnDst.  This is 0 if the node is not turning.
	*/
	float dr;

	/** the angle that the node is currently rotating towards.
	* the dr value is added to the node's rotation until it is equal to this value
	*/
	float turnDst;

	/** the maximum turning speed of the node.
	* this is the absolute value of the greatest positive or negative value that dr may achieve.
	*/
	float turnSpeed;

	/** the children of the node.
	* a std::set of entities representing the children of this node.
	*/
	std::set<Entity*> children;

public:
	Node(float X=0.0, float Y=0.0, float Z=0.0, float R=0.0);

	/** update all the children of the node.
	* this will call the update function of all the entities belonging to this node.
	*/
	void Update();

	/** apply appropriate transformations and draw all of the children of the node.
	* this will rotate and translate the node according to the x,y,z and rot values and then call the draw function of all the entities belonging to this node.
	*/
	void Draw();

	/** adds the passed child to the node's children.
	* inserts the given entity.  what more do you want? :-|
	*/
	void AddChild(Entity* child) {children.insert(child);}

	/** removes the passed child from the node's children.
	* removes the given entity from children.
	*/
	void RemoveChild(Entity* child) {children.erase(child);}

	/** turns the node towards the given (x,y) pair point.
	* calculates the angle needed to turn to the specified point and sets turnDst accordingly.
	*/
	void Face(float dstX, float dstY);

	float GetX() {return x;}
	float GetY() {return y;}
	float GetZ() {return z;}
	float GetRot() {return rot;}
	float GetDY() {return dY;}
	float GetDX() {return dX;}
	float GetTurnSpeed() {return turnSpeed;}
	float GetTurnDst() {return turnDst;}
	Vector2 GetCenter() {return Vector2(x, y);}

	void SetX(float X) {x=X;}
	void SetY(float Y) {y=Y;}
	void SetZ(float Z) {z=Z;}
	void SetDX(float d) {dX=d;}
	void SetDY(float d) {dY=d;}
	void SetRot(float r) {rot=r;}
	void SetTurnSpeed(float t) {turnSpeed=t;}
	void SetTurnDst(float d) {turnDst=d;}
	/* sets the new center for the node.
	* if no Z is given, the old Z is kept.
	*/
	void SetCenter(float X=0.0, float Y=0.0, float Z=NULL) {x=X; y=Y; if(z != NULL) z=Z;}
};

#endif
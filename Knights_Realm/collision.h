#ifndef _COLLISION_H
#define _COLLISION_H

#include <string>
#include "krutil.h"
#include "entity.h"
#include "eventmgr.h"
#include "node.h"

class ColNode : public Entity {
protected:
	/** The name referring to this collison node.
	*/
	std::string name;
public:
	virtual bool Check(ColNode* c) {return false;}

	std::string GetName() {return name;}
};

class ColRect : public ColNode {
	/** The parent node for this collision node.
	* The parent node is used to determine the position of the collision rectangle.
	*/
	Node* parent;

	/** The width of the collision rect.
	* This is the distance from the center of the node in each direction, so it is half of the actual width.
	*/
	float w;

	/** The height of the collision rect.
	* This is the distance from the center of the node in each direction, so it is half of the actual height.
	*/
	float h;

public:
	ColRect(std::string n, float W, float H, Node* par) {name=n; w=W; h=H; parent=par;}
	
	/** Check collision between this rectangle and another.
		Props to Oren Becker, 2001. I didn't make this algorithm.
		@param other	The collision node to check agains this collison rect.
		@return			True if this colRect is colliding with other.
	*/
	bool Check(ColRect* other);

	/** Get a vector containing the size (w & h) of this collison rectangle.
		@return		A Vector2 containing the width and height of the collision rectangle.
		@sa krutil
	*/
	Vector2 GetSize() {return Vector2(w, h);}

	/** Get the collision rectangle's width.
		@return		The width of the collision rectangle.
	*/
	float GetW() {return w;}

	/** Get the collision rectangle's height.
		@return		The height of the collision rectangle.
	*/
	float GetH() {return h;}
};

class ColTraverser : public Entity {
	/** The nodes to check collision between.
	*/
	std::set<ColRect*> nodes;		// TODO: nodes
public:
	ColTraverser() {}

	/** Traverse all collision nodes and trigger events.
	* this sends a collision message of the form (name of first collision node)-into-(name of second collision node) to the given event manager.
	*/
	void Traverse(EvtMgr* evtMgr);

	/** Add a new collision node to the collision traverser.
		The passed collision node is added to the traverser and checked for collisions
		with other collison nodes that are also in the traverser.
		@param		The collision node to add to the traverser
	*/
	void AddNode(ColRect* c) {nodes.insert(c);}	// TODO: rect
};

#endif

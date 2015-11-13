#ifndef _AI_H
#define _AI_H

#include <map>
#include <vector>
#include "micropather.h"
#include "map.h"
#include "entity.h"
#include "node.h"

using namespace std;
using namespace micropather;

class AIComponent : Entity {
	/** operators for the ai queue.
	*/
	enum AIOp {halt, flee, wander,
		seek_nearest_foe, seek_farest_foe, 
		fight_until_death, fight_until_danger, fight_with_range,
		wait_until_attacked, wait_until_foe_in_range
	};

	/** The field of view for this ai component.
	*/
	float fov;

	/** The radius of view for this ai component.
	*/
	float rangeOfVision;

	/** The parent node that this component is attached to.
	*/
	Node* parentNode;

	/** a queue of actions to perform.
	* a binary queue of actions to perform before the next update.
	*/
	vector<unsigned short> queue;

	/** The path to follow.
	* The A* generated path to follow.
	*/
	vector<void*> path;

	/** The micropather A* path-finder.
	*/
	MicroPather* pather;

	/** Functions for the AI queue operators.
	*/
	bool Halt();
	bool Flee();
	bool Wander();
	bool SeekNearestFoe();
	bool SeekFarestFoe();
	bool FightUntilDeath();
	bool FightUntilDanger();
	bool FightWithRange();
	bool WaitUntilAttacked();
	bool WaitUntilFoeInRange();


public:
	AIComponent(Graph* map);
	
	/** 
		Find a path to the target position from the current position.
		Use A* to find a path to the give (x,y) position
		@param targetX	The x coordinate to solve a path for.
		@param targetY	The y coordinate to solve a path for.
		@return			True if there is a path to the target, false if there is no path or the destination is the same as the start.
	*/
	bool FindPath(int targetX, int tagetY);

	void Update();
	void onReachNode();
	void onUpdate();
	void onCollide();
};

#endif
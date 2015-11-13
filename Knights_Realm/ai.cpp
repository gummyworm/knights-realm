#include "ai.h"

using namespace micropather;

AIComponent::AIComponent(Graph* map)
{
	pather = new MicroPather(map);
}

void AIComponent::Update()
{
	// Call the proper update function. If it returns false,
	// remove the current operator
	switch(queue.at(0)) {
	case halt: if(Halt()) return; break;
	case wander: if(Wander()) return; break;
	}
	queue.erase(queue.begin());
}

bool AIComponent::Halt()
{
	// stop the node 
	parentNode->SetDX(0);
	parentNode->SetDY(0);
	// TODO: stop the animation

	return true;
}

bool AIComponent::Wander()
{
	return false;
}

bool AIComponent::FindPath(int x, int y)
{
	float cost;
	if(pather->Solve((void*)x, (void*)y, &path, &cost) != pather->SOLVED)
		return false;
	return true;
}
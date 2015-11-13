#ifndef _PLAYER_H
#define _PLAYER_H

#include "sprite.h"

class Player: public Sprite {
	int hp, attack, defense;
public:
	Player(std::string filename="");
};

#endif


#include "player.h"

Player::Player(std::string filename) : Sprite(filename)
{
    colW=32;
    colH=32;

    sSheetW=512; 
    sSheetH=512;
	colW=0;
	colH=0;
//    colW=cW;
//    colH=cH;
}

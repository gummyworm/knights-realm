#ifndef _MAP_H
#define _MAP_H

#define NUM_LAYERS 5
#define COLLISION_LAYER 4

#include <string>
#include <iostream>
#include <vector>
#include <string.h>
#include "micropather.h"
#include "SDL.h"
#include "SDL_opengl.h"
#include "tinyxml/tinyxml.h"
#include "tinyxml/tinystr.h"
#include "sprite.h"
#include "texture.h"

using namespace std;
using namespace micropather;

class Map : Graph {
	// map properties
	int mapW, mapH;
	unsigned int tileMap[NUM_LAYERS][100000];
	int numLayers;
	GLuint tilesheetTex;
	string mapName;
	string mapFileName;

	// tile properties
	int tilesheetW, tilesheetH;
	int tileW, tileH, tileSpacing, tileMargin;
	int gid0;

	SDL_Surface* tileSheet;

public:
	Map() {tilesheetW=512; tilesheetH=512; tileMargin=0; tileSpacing=0;}
	Map(string mapName) {Load(mapName);}
	void Load(string mapName);
	void DecodeB64(const char data[], int layer);
	void Render();
	void Update();
	bool IsMoveLegal(int x, int y, int w, int h);
	unsigned int GetTile(int layer, int idx) {return tileMap[layer][idx];}

	// micropather functions
	float LeastCostEstimate(void* stateStart, void* stateEnd);
	void AdjacentCost(void* state, std::vector<StateCost> *adjacent);
	virtual void  PrintStateInfo(void* state) {}

	int GetMapW() {return mapW;}
	int GetMapH() {return mapH;}
	int GetTileW() {return tileW;}
	int GetTileH() {return tileH;}
	int GetTileMargin() {return tileMargin;}
	int GetTileSpacing() {return tileSpacing;}
};

#endif


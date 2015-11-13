#ifndef _GAME_H
#define _GAME_H

#include <iostream>
#include <vector>
#include <set>
#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_opengl.h"
#include "SDL_ttf.h"
#include "fastdelegate/FastDelegate.h"
#include "entity.h"
#include "node.h"
#include "sprite.h"
#include "texture.h"
#include "map.h"
#include "collision.h"
#include "camera.h"
#include "particle.h"
#include "player.h"
#include "frame.h"
#include "timer.h"
#include "eventmgr.h"

#define FRAMES_PER_SECOND 60

// graphics properties
#define ABLEND TRUE
#define ATEST TRUE
#define ZORDER TRUE

class Game {
	// TODO:
	int test;

	// the SDL event
	SDL_Event event;

	// game objects... there are few types
	Camera camera;

	/** the tile map.
	* this contains the currently active map to be drawn each frame.
	*/
	Map map;
	Player player;
	Node playerNode;	// TODO: delete like a bad sack'a'potatoes

	/** the set of game entities. 
	* this contains all the game entities that are updated and drawn each frame.
	*/
	GameEntity entities;

	/** the collision traverser.
	* this is used for detecting collision between collision nodes.  To check collision against something, its collision node
	* must be added to this traverser.
	*/
	ColTraverser cTrav;

	// screen properties
	SDL_Surface* screen;
	int screenW, screenH, screenBPP;

	// technical properties
	bool frameCap;
	Timer fps;

	/** the keys that are currently pressed on the keyboard.
	* the key state (keys pressed) of the current frame.  These are updated every time the engine ticks.
	*/
	Uint8 *keyStates;

	/** the x coordinate of the mouse.
	* the x coordinate of the mouse as read by SDL.
	*/
	int mouseX;

	/** the y coordinate of the mouse.
	* the y coordinate of the mouse as read by SDL.
	*/
	int mouseY;

	/** the state of the left mouse button.
	* the state of the left mouse button during the current frame. True means the button is pressed.
	*/
	bool mouseLDown;

	/** the state of the right mouse button.
	* the state of the right mouse button during the current frame. True means the button is pressed.
	*/
	bool mouseRDown;

	/** the manager for sending and receiving events.
	*
	*/
	EvtMgr* evtmgr;

public:
	Game();
	~Game();

	void Setup();
	void Run();
	bool Tick();

	void AddEntity(Entity* e) {entities.insert(e);}
	void AddCollider(ColRect* c) {cTrav.AddNode(c);}	// TODO: not just ColRects..

	void AddMap(std::string mapName) {map.Load(mapName);}
	void AddPlayer(Player newPlayer) {player = newPlayer;}
	void AddTextBox(Entity *textBox) {entities.insert(textBox);}

	void Accept(std::string name, Entity* e, PyObject* pyFunc) {evtmgr->BindPy(name, e, pyFunc);}

	void SetTest(int t) {std::cout<<"SETTTTTTTTTTTING" << std::endl; test = t;}
	int GetTest() {return test;}
};

//static Game game;
//Game& GetGame();

#endif

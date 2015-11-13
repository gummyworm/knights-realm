#ifndef _SPRITE_H
#define _SPRITE_H

#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <cmath>
#include "SDL.h"
#include "SDL_opengl.h"
#include "entity.h"
#include "animation.h"
#include "rect.h"
#include "map.h"
#include "krutil.h"
#include "script.h"
#include "tinyxml/tinyxml.h"
#include "tinyxml/tinystr.h"

class Sprite : public Entity{
protected:
	int colW;
	int colH;

	int xScale, yScale;
	int sSheetW, sSheetH;
	RectTextured* rect;
	RectTextured* restoreRect;

	Animation* animMgr;
	Script* script;

public:
	//Sprite(int W=32, int H=64, GLuint tex=0, int cX=32, int cY=32, int cW=32, int cH=32);
	Sprite(std::string filename);

	void Update();
	void Draw();
	void Load(std::string filename="");

	void PlayAnimation(std::string anim) {animMgr->Play(anim);}
	void LoopAnimation(std::string anim) {animMgr->Loop(anim);}
	void Pose(int f) {animMgr->Pose(f);}

	/** set the delta rotation so that this sprite will face the given x, y coordinate.
	* change the delta rotation to a value that will make the sprite face the given x, y coordinate in the shortest number of frames possible.
	* the dr is limited by the sprite's maximum turning speed.
	*/
	int GetW() {return rect->GetW();}
	int GetH() {return rect->GetH();}
	GLuint GetTexture() {return rect->GetTexture();}
	int GetFrame() {return animMgr->GetFrame();}
	int GetSSheetW() {return sSheetW;}
	int GetSSheetH() {return sSheetH;}
	int GetColW() {return colW;}
	int GetColH() {return colH;}
	Script* GetScript() {return script;}

	//void SetAnimation(int a) {animation=a; frame=animations[a].frameStart;}
	void SetRect(RectTextured *r) {rect=r;}
	void SetTexture(GLuint t) {rect->SetTexture(t);}
};

#endif


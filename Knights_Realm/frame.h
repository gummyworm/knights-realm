#ifndef _FRAME_H
#define _FRAME_H

#include <vector>
#include <set>
#include "entity.h"
#include "SDL_opengl.h"
#include "rect.h"

typedef std::set<Entity*> FrameEntity;

class Frame : public RectTextured {
protected:
	FrameEntity contents;
public:
	Frame() {w=500; h=200; tags=new std::set<std::string>; name="";}
	Frame(GLuint Tex, int x=0, int y=0, int z=98, int w=500, int h=200);

	virtual void Draw();
	virtual void Add(Entity *e) {contents.insert(e);}
};

class TabbedFrame : public Frame {
	/* the frame for the tabs that are closed */
	Frame closedFrame;
	/* the frame for the tab that is opened */
	Frame openedFrame;

	/* the text displayed on each tab */
	std::vector<std::string> tabsText;
	/* the frames (correspomding to each tab */
	std::vector<Frame> frames;

	/* the currently opened tab index */
	int currentlyOpen;

public:
	TabbedFrame(Frame tabClosed, Frame tabOpened, int W=500, int H=500, int initialFrame=0);
	void AddFrame(Frame frame, bool setToOpen=false);
	void Draw();

	void SetOpen(int i) {currentlyOpen = i;}
};

#endif


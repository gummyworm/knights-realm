#include "frame.h"
Frame::Frame(GLuint Tex, int X, int Y, int Z, int W, int H) : RectTextured(W, H, Tex)
{
    clipX=0;
    clipY=0;
    clipW=1;
    clipH=1;
	name="";
	tags=new std::set<std::string>;
}

void Frame::Draw()
{
	glPushMatrix();
	for(FrameEntity::iterator it = contents.begin(); it != contents.end(); it++) {
        (*it)->Update();
    }
	for(FrameEntity::iterator it = contents.begin(); it != contents.end(); it++) {
        (*it)->Draw();
    }
	glPopMatrix();
}

TabbedFrame::TabbedFrame(Frame tabClosed, Frame tabOpened, int W, int H, int initialFrame) : Frame()
{
	w=W;
	h=H;
	closedFrame = tabClosed;
	openedFrame = tabOpened;
}

void TabbedFrame::AddFrame(Frame newFrame, bool setToOpen)
{
	frames.push_back(newFrame);
}

void TabbedFrame::Draw()
{
	// draw the currently open frame
	//frames[currentlyOpen].Draw();
}

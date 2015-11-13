#include "animation.h"

void Animation::Update()
{
	if(playing) {
		waitFrames--;
		if(waitFrames == 0) {
			waitFrames=frameDelay;		// reset frame delay
			if(frame < stopFrame) {
				frame++;
			}
			else {
				if(loop) {
					frame=animations.find(activeAnim)->second.startFrame;	// reset the frame to the starting frame
				}
			}
		}
	}
}

void Animation::Play(std::string anim)
{
	frame=animations.find(anim)->second.startFrame;
	stopFrame=animations.find(anim)->second.stopFrame;
	waitFrames=animations.find(anim)->second.frameDelay;
	frameDelay=waitFrames;
	loop=false;
	playing=true;
}

void Animation::Loop(std::string anim)
{
	frame=animations.find(anim)->second.startFrame;
	stopFrame=animations.find(anim)->second.stopFrame;
	waitFrames=animations.find(anim)->second.frameDelay;
	frameDelay=waitFrames;
	loop=true;
	playing=true;
}

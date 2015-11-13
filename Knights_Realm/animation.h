#ifndef _ANIMATION_H
#define _ANIMATION_H

#include <map>
#include <iostream>
#include <string>
#include "tinyxml/tinyxml.h"
#include "tinyxml/tinystr.h"

typedef struct {
	/** the clip given by the integer index of the tilesheet to start the animation at.
	*
	*/
	int startFrame;

	/** the tilesheet frame clip to stop the animation at.
	*
	*/
	int stopFrame;

	/** the number of frames that will elapse before the next frame is displayed.
	*
	*/
	int frameDelay;
}AnimElement;

class Animation {
private:
	/** the map of all animations loaded into this instance.
	* the key is a string that represents the name of the animation being referred to, and the corresponding value is the corresponding animation
	* element.
	*/
	std::map<std::string, AnimElement> animations;

	/** the currently active animation.
	*
	*/
	std::string activeAnim;

	/** the active frame in the current animation.
	*
	*/
	int frame;

	/** determines if frames should be advanced in update.
	*
	*/
	bool playing;

	/** determines if the frames for the active animation should be looped.
	*
	*/
	bool loop;

	/** the number of frames that will pass before the next frame is displayed.
	* this will count down to zero at which point the value will be reset to the value of in the active AnimElement (if any).  
	*/
	int waitFrames;

	/** the current frame delay (same as the frameDelay value in the current animation element).
	*
	*/
	int frameDelay;

	/** the frame to stop the animation on (same as the frameStop value in the currently active animation element).
	*
	*/
	int stopFrame;

public:
	void Update();

	/** add the animation represented by the given parameters.
	*
	*/
	void AddAnimation(std::string name, int start, int stop, int speed) {AnimElement a={start, stop, speed}; animations.insert(std::pair<std::string, AnimElement>(name, a));}

	/** plays the given animation once.
	* if a new animation action (Loop or Play) is called during this, it will replace the previously active one.
	*/
	void Play(std::string anim);

	/** run the given animation repeatedly.
	* the given animation is run until it is "Paused", "Stopped", or replaced with a new Play or Loop.
	*/
	void Loop(std::string anim);

	/** pause the currently running frame.
	* the active frame state is not destroyed. calling "UnPause" will continue where the animation left off. if it is already paused, this will do nothing.
	*/
	void Pause() {playing=false;}

	/** unpause the currently active animation.
	* this will simply continue running the active animation on the frame where it was paused. if it is already playing, this will do nothing.
	*/
	void UnPause() {playing=true;}

	/** stop the currently running animation and reset it to its first frame.
	*
	*/
	void Stop() {playing=false; frame=animations.find(activeAnim)->second.startFrame;}

	/** set the frame to the given frame #
	*
	*/
	void Pose(int f) {frame=f;}

	int GetFrame() {return frame;}
};

#endif
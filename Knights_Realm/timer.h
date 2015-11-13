#ifndef _TIMER_H
#define _TIMER_H

class Timer {
	int startTicks;
	int pausedTicks;
	bool paused, started;

public:
	Timer() {startTicks=0; pausedTicks=0; paused=false; started=false;}

	void Start() {started=true; paused=false; startTicks=SDL_GetTicks();}
	void Stop() {started=false; paused=false;}

	void Pause() { if((started==true) && (paused==false)) {
		paused=true; pausedTicks=SDL_GetTicks()-startTicks;} }

	void Unpause() { if(paused==true) {
		paused=false; startTicks=SDL_GetTicks()-pausedTicks; pausedTicks=0;} }

	int GetTicks() { if(started==true) { 
		if(paused==true) return pausedTicks;
		else return SDL_GetTicks()-startTicks;} }

	bool IsStarted() {return started;}
	bool IsPaused() {return paused;}

};

#endif

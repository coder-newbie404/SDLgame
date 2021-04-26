#ifndef SCORE__H_
#define SCORE__H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <sstream>

using namespace std;

//The application time based timer
struct LTimer
{
		Uint32 mStartTicks = 0;

		Uint32 mPausedTicks = 0;

		bool mPaused = false;
		bool mStarted = false;

		void start();
		void stop();
		void pause();
		void unpause();

		Uint32 getTicks();

		bool isStarted();
		bool isPaused();


};

#endif

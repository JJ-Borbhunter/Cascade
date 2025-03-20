#include <SDL3/SDL.h>

const int FRAMEDELAY = 1000/30;


void framelimit(){
	static int framestart = SDL_GetTicks();

	int frametime = SDL_GetTicks() - framestart;
	if (frametime < FRAMEDELAY) {
		SDL_Delay(FRAMEDELAY - frametime);
	}
	framestart = SDL_GetTicks();
}
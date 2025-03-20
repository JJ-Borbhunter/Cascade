#include "Display.hpp"
#include <iostream>
using namespace std;

#include <SDL3/SDL.h>
#include <GL/gl3w.h>
#include <SDL3/SDL_opengl.h>
#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_opengl3.h>

#include "error.hpp"

const char* CURSOR_PATH = "resources/texture/cursor.bmp";
const int DESIRED_SCREEN_WIDTH = 1200;


//#define DEBUG_WINDOWED
//#undef DEBUG_WINDOWED

Display::Display(const char* name, int fOGL_Version_Major, int fOGL_Version_Minor){

	SDL_DisplayID* displays;
	const SDL_DisplayMode* DM;

	SDL_Init(SDL_INIT_VIDEO);

	displays = SDL_GetDisplays(NULL);
	DM = SDL_GetDesktopDisplayMode(displays[0]);
	SDL_free(displays);

#ifndef DEBUG_WINDOWED
	iWidth = DM->w;
	iHeight = DM->h;

    if ((float)iWidth/iHeight < 4.0/3.0) {
        iHeight = iWidth * .75;
        pWindow = SDL_CreateWindow(name, iWidth, iHeight, 
            SDL_WINDOW_OPENGL
        );
    } else {
        pWindow = SDL_CreateWindow(name, iWidth, iHeight, 
            SDL_WINDOW_OPENGL |
            SDL_WINDOW_FULLSCREEN
        );
    }
#endif
#ifdef DEBUG_WINDOWED
    iWidth = DM->w/2.0f;
    iHeight = DM->h/2.0f;


    pWindow = SDL_CreateWindow(name, iWidth, iHeight, 
        SDL_WINDOW_OPENGL
    );
#endif


	if( pWindow == nullptr ) {
            error_raise("Window could not be created! SDL_Error: ", SDL_GetError());
            return;
    }
       // Set up for OpenGL
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, fOGL_Version_Major);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, fOGL_Version_Minor);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    cContext = SDL_GL_CreateContext(pWindow);
    if (cContext == nullptr) {
        error_raise("Failed to create GL context", "");
        SDL_DestroyWindow(pWindow);
        SDL_Quit();
        return;
    }

    SDL_GL_MakeCurrent(pWindow, cContext);
    if(gl3wInit() != 0){
        error_raise("Failed to initialize gl3w in Display::Display(): ", "");
    }
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    //Set custom cursor
    SDL_Surface *surface = NULL;
    SDL_Cursor *cursor = NULL;
    surface = SDL_LoadBMP(CURSOR_PATH);
    if (!surface) {
        error_raise("Nonfatal error, cursor Failed to load: ", CURSOR_PATH);
    }
    cursor = SDL_CreateColorCursor(surface, 0, 0);
    SDL_SetCursor(cursor);
    SDL_DestroySurface(surface);
}

Display::~Display(){
	SDL_DestroyWindow(pWindow);
}


void Display::update() const {
	SDL_GL_SwapWindow(pWindow);
    glClear(GL_COLOR_BUFFER_BIT);
}






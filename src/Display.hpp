#pragma once
#include <SDL3/SDL.h>


class Display {
public:
	Display();
	Display(const char* name, int fOGL_Version_Major, int fOGL_Version_Minor);
	~Display();
	void destroy();
	void update() const ;
	int get_width() const { return iWidth; };
	int get_height() const { return iHeight; };
	SDL_Window* get_window() const { return pWindow; }
	SDL_GLContext get_context() const { return cContext; }

private:
	int iWidth;
	int iHeight;
	SDL_Window* pWindow;
	SDL_GLContext cContext;
};
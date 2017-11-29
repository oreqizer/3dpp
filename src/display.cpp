#include "display.h"
#include <iostream>

Display::Display(int width, int height, const std::string& title) {
	SDL_Init(SDL_INIT_EVERYTHING);

	// Sets up OpenGL stuff
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8); // 2^8
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // Allocates memory for a 2nd, virtual window

	SDL_Window* m_window = SDL_CreateWindow(
		title.c_str(), // SDL is a C API, needs C types
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
		SDL_WINDOW_OPENGL // uses OpenGL
	);
}

Display::~Display() {
	SDL_Quit();
}

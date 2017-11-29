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
	// Allocates memory for a 2nd, virtual window
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	m_window = SDL_CreateWindow(
		title.c_str(), // SDL is a C API, needs C types
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
		SDL_WINDOW_OPENGL // uses OpenGL
	);

	// Tells OS to make the window listen to the GPU
	// instead of the OS itself
	m_glContext = SDL_GL_CreateContext(m_window);
}

void Display::swapBuffers() {
	// Swaps the real and the virtual window buffer
	SDL_GL_SwapWindow(m_window);
}

Display::~Display() {
	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

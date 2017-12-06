#include <iostream>
#include <GL/glew.h>

#include "display.h"

Display::Display(int width, int height, const std::string& title) {
	SDL_Init(SDL_INIT_EVERYTHING);

	// Sets up OpenGL stuff
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8); // 2^8
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	// For hidden surface removal
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
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

	// A YouTube comment told me to do this ¯\_(ツ)_/¯
	glewExperimental = GL_TRUE;
	// Searches the OS and gathers all possible OpenGL fns
	GLenum status = glewInit();

	if (status != GLEW_OK) {
		std::cout << "Glew failed to initialize" << std::endl;
	}

	m_isClosed = false;

	// Hidden surface removal
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

Display::~Display() {
	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void Display::Update() {
	// Swaps the real and the virtual window buffer
	SDL_GL_SwapWindow(m_window);

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			m_isClosed = true;
		}
	}
}

void Display::Clear(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool Display::IsClosed() {
	return m_isClosed;
}

#ifndef DISPLAY_INCLUDED_H
#define DISPLAY_INCLUDED_H

#include <string>
#include <SDL2/SDL.h>

class Display {
    public:
        Display(int width, int height, const std::string& title);
        void swapBuffers();

        virtual ~Display();
    protected:
    private:
        void operator=(const Display& display) {}
        Display(const Display& display) {}
        
        SDL_Window* m_window;
        SDL_GLContext m_glContext;
};

#endif // DISPLAY_H

#ifndef DISPLAY_INCLUDED_H
#define DISPLAY_INCLUDED_H

#include <string>
#include <SDL2/SDL.h>

class Display {
    public:
        Display(int width, int height, const std::string& title);

        virtual ~Display();
    protected:
    private:
        void operator=(const Display& display) {}
        Display(const Display& display) {}
        
        SDL_Window* window_m;
};

#endif // DISPLAY_H

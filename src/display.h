#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>
#include <SDL2/SDL.h>

class Display {
public:
    Display(int width, int height, const std::string& title);
    virtual ~Display();

    void Update();
    void Clear(float r, float g, float b, float a);
    bool IsClosed();
protected:
private:
    void operator=(const Display& display) {}
    Display(const Display& display) {}
    
    SDL_Window* m_window;
    SDL_GLContext m_glContext;
    bool m_isClosed;
};

#endif // DISPLAY_H

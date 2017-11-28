#ifndef DISPLAY_INCLUDED_H
#define DISPLAY_INCLUDED_H

#include <string>

class Display {
    public:
        Display(int width, int height, const std::string& title);

        virtual ~Display();
    protected:
    private:
        void operator=(const Display& display) {}
	    Display(const Display& display) {}
};

#endif

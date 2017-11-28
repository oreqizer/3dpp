#include "display.h"
#include <iostream>

Display::Display(int width, int height, const std::string& title) {
	std::cout << "Alive" << std::endl;
}

Display::~Display() {
	std::cout << "Dead" << std::endl;
}

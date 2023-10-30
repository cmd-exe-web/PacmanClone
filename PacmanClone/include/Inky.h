#pragma once

#include "Ghost.h"
#include "Blinky.h"

class Inky : public Ghost {
public:
	Inky();
	Inky(SDL_Renderer* renderer);
	void Update(Maze& maze, Pacman& pacman, Blinky& blinky);
	SDL_Point CalculateInkysTarget(Pacman& pacman, Blinky& blinky);
private:
	Uint32 lastModeChange;

};

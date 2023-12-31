#pragma once

#include "Ghost.h"
#include "Maze.h"

class Blinky : public Ghost {
public:
	Blinky();
	Blinky(SDL_Renderer* renderer);
	void Update(Maze& maze, Pacman& pacman) override;
private:
	Uint32 lastModeChange;
};

#pragma once


#include "Ghost.h"
#include "Maze.h"

class Pinky : public Ghost {
public:
	Pinky();
	Pinky(SDL_Renderer* renderer);
	void Update(Maze& maze, Pacman& pacman) override;
private:
	Uint32 lastModeChange;
};


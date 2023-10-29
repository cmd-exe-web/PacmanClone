#pragma once

#include "Ghost.h"
#include "Maze.h"

class Blinky : public Ghost {
public:
	Blinky();
	Blinky(SDL_Renderer* renderer);
	void Update(Maze& maze, Pacman& pacman) override;
private:
	SDL_Point scatterTarget{MAZE_WIDTH - TILE_SIZE, -1 * TILE_SIZE};
};

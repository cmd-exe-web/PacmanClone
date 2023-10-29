#pragma once

#include "Ghost.h"

class Inky : Ghost {
public:
	Inky();
	Inky(SDL_Renderer* renderer);
	void Update(Maze& maze, Pacman& pacman) override;
private:

};

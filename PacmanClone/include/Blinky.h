#pragma once

#include "Ghost.h"
#include "Maze.h"

class Blinky : public Ghost {
public:
	Blinky();
	void Update(Maze& maze, Pacman& pacman) override;
	void Draw() override;
private:

};

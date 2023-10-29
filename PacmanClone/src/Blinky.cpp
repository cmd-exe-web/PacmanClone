#include "Blinky.h"

Blinky::Blinky()
{
}

Blinky::Blinky(SDL_Renderer* renderer)
	:Ghost(renderer)
{
	ghostType = GhostType::Blinky;
	x = (20 * 15);
	y = (20 * 11);
}

void Blinky::Update(Maze& maze, Pacman& pacman)
{
	ChaseTarget({scatterTarget}, maze);
}


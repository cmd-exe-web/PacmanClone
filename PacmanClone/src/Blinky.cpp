#include "Blinky.h"

Blinky::Blinky()
{
}

Blinky::Blinky(SDL_Renderer* renderer)
	:Ghost(renderer)
{
	ghostType = GhostType::Blinky;
	x = (20 * 14);
	y = (20 * 11);
	currentMode = Mode::Chase;
	lastModeChange = SDL_GetTicks();
	scatterTarget = {MAZE_WIDTH - TILE_SIZE, -10 * TILE_SIZE};
}

void Blinky::Update(Maze& maze, Pacman& pacman)
{
	Uint32 timeSinceLastChange = SDL_GetTicks() - lastModeChange;
	if (currentMode == Mode::Chase && timeSinceLastChange >= 20000)
	{
		currentMode = Mode::Scatter;
		currentDirection = GetReverseDirection(currentDirection);
		lastModeChange = SDL_GetTicks();
	}
	else if (currentMode == Mode::Scatter && timeSinceLastChange >= 7000) {
		currentDirection = GetReverseDirection(currentDirection);
		currentMode = Mode::Chase;
		currentDirection = GetReverseDirection(currentDirection);
	}


	if (currentMode == Mode::Chase) {
		ChaseTarget({ pacman.x, pacman.y }, maze);
	}
	else if (currentMode == Mode::Scatter) {
		ChaseTarget({ scatterTarget }, maze);
	}
}


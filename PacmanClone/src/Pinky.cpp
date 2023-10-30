#include "Pinky.h"

Pinky::Pinky()
{
}

Pinky::Pinky(SDL_Renderer* renderer)
	:Ghost(renderer)
{
	ghostType = GhostType::Pinky;
	x = (20 * 13);
	y = (20 * 14);
	currentMode = Mode::Chase;
	lastModeChange = SDL_GetTicks();
	scatterTarget = {0, -10 * TILE_SIZE};
}

void Pinky::Update(Maze& maze, Pacman& pacman)
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
		int targetX = x;
		int targetY = y;
		if (pacman.currentDirection == Right) targetX += 4 * TILE_SIZE;
		if (pacman.currentDirection == Left)  targetX -= 4 * TILE_SIZE;
		if (pacman.currentDirection == Up)    targetY -= 4 * TILE_SIZE;
		if (pacman.currentDirection == Down)  targetY += 4 * TILE_SIZE;
		ChaseTarget({ targetX, targetY }, maze);
	}
	else if (currentMode == Mode::Scatter) {
		ChaseTarget({ scatterTarget }, maze);
	}
}

#include "Inky.h"

Inky::Inky()
{
}

Inky::Inky(SDL_Renderer* renderer)
	:Ghost(renderer)
{
	ghostType = GhostType::Inky;
	x = (20 * 12);
	y = (20 * 14);
	currentMode = Mode::Chase;
	lastModeChange = SDL_GetTicks();
	scatterTarget = {MAZE_WIDTH, MAZE_HEIGHT};
}

void Inky::Update(Maze& maze, Pacman& pacman, Blinky& blinky)
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
		int distanceFromPacman = GetDistance({ pacman.x, pacman.y }, { x, y });
		if (distanceFromPacman > 6 * TILE_SIZE) {
			SDL_Point inkysTarget = CalculateInkysTarget(pacman, blinky);
			ChaseTarget(inkysTarget, maze);
		}
		else {
			ChaseTarget({ pacman.x, pacman.y }, maze);
		}
	}
	else if (currentMode == Mode::Scatter) {
		ChaseTarget({ scatterTarget }, maze);
	}
}

SDL_Point Inky::CalculateInkysTarget(Pacman& pacman, Blinky& blinky)
{
	int pacmanOffsetX = x;
	int pacmanOffsetY = y;
	if (pacman.currentDirection == Right) pacmanOffsetX += 2 * TILE_SIZE;
	if (pacman.currentDirection == Left)  pacmanOffsetX -= 2 * TILE_SIZE;
	if (pacman.currentDirection == Up)    pacmanOffsetY -= 2 * TILE_SIZE;
	if (pacman.currentDirection == Down)  pacmanOffsetY += 2 * TILE_SIZE;

	int VectorX = 2 * pacmanOffsetX - blinky.x;
	int VectorY = 2 * pacmanOffsetY - blinky.y;

	int inkyTargetX = VectorX + blinky.x;
	int inkyTargetY = VectorY + blinky.y;
	return { inkyTargetX, inkyTargetX };
}


#pragma once

#include <SDL2/SDL.h>

#include <vector>

#include "Constants.h"
#include "Maze.h"
#include "Pacman.h"

enum Mode {
	Chase, Scatter, Scared
};

struct Channels {
	bool left = false;
	bool right = false;
	bool up = false;
	bool down = false;
	int count = 0;
};

enum GhostType {
	Blinky, Inky, Pinky, Clyde
};

class Ghost {
public:
	Ghost();
	Ghost(SDL_Renderer* renderer);
	virtual void Update(Maze& maze, Pacman& pacman);
	void MoveRandomly(Maze& maze);
	std::vector<Direction> TurnsAvailable(Maze& maze);
	bool CanMove(float x, float y, Maze maze);
	Direction ClosestPath(SDL_Point target);
	bool CoincidesIntersection(float x, float y, Maze& maze);
	virtual void Draw();
private:
	int x, y;
	float velocity = 1;
	Direction currentDirection;
	SDL_Renderer* renderer;

	SDL_Point target;
	Mode currentMode;

	GhostType ghostType = Blinky;
	SDL_Texture* texture;
	int frameWidth, frameHeight;
};

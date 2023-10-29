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

enum class GhostType : int {
	Blinky, Inky, Pinky, Clyde
};

class Ghost {
public:
	Ghost();
	Ghost(SDL_Renderer* renderer);
	virtual void Update(Maze& maze, Pacman& pacman);
	void ChaseTarget(SDL_Point target, Maze& maze);
	void MoveRandomly(Maze& maze);
	Direction GetReverseDirection(Direction direction);
	std::vector<Direction> TurnsAvailable(Maze& maze);
	bool CanMove(float x, float y, Maze maze);
	bool CoincidesIntersection(float x, float y, Maze& maze);
	void SetTarget(SDL_Point target);
	std::vector<Direction> ClosestPath(SDL_Point target);
	float GetDistance(SDL_Point point1, SDL_Point point2);
	void Draw();
protected:
	GhostType ghostType;
	int x, y;
private:
	float velocity = 1;
	Direction currentDirection;
	SDL_Renderer* renderer;

	SDL_Point currentTarget;
	Mode currentMode;

	SDL_Texture* texture;
	int frameWidth, frameHeight;
};

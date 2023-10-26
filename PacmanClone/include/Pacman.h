#pragma once

#include <SDL2/SDL.h>

#include "Constants.h"
#include "Maze.h"

class Pacman {
public:
	Pacman();
	Pacman(SDL_Renderer* renderer);
	void HandleInput(SDL_Keycode key);
	void Update(Maze maze);
	bool CanMove(float x, float y, Direction direction, Maze maze);
	void Draw();
public:
	int x, y;
	int velocity = 1;
	Direction currentDirection;
	Direction newDirection;

	SDL_Renderer* renderer;

	SDL_Texture* texture;
};

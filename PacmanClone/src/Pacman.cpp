#include <SDL2/SDL_image.h>

#include <iostream>

#include "Pacman.h"

Pacman::Pacman()
{
}

Pacman::Pacman(SDL_Renderer* renderer)
	:x(20), y(20), renderer(renderer)
{
	IMG_Init(IMG_INIT_PNG);

	currentDirection = right;
	newDirection = none;

	SDL_Surface* surface = IMG_Load("assets/images/pacmansprite-1.png");
	if (surface == nullptr) {
		std::cerr << "Couldn't Load Image. Error: " << SDL_GetError() << std::endl;
		std::cin.get();
		exit(EXIT_FAILURE);
	}
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == nullptr) {
		std::cerr << "Couldn't create texture from iamge. Error: " << SDL_GetError() << std::endl;
		std::cin.get();
		exit(EXIT_FAILURE);
	}
	SDL_FreeSurface(surface);
}

void Pacman::HandleInput(SDL_Keycode key)
{
	if (key == SDLK_w) {
		newDirection = up;
	}
	if (key == SDLK_a) {
		newDirection = left;
	}
	if (key == SDLK_s) {
		newDirection = down;
	}
	if (key == SDLK_d) {
		newDirection = right;
	}
}

void Pacman::Update(Maze maze)
{
	int newX = x;
	int newY = y;
	// Check to see if you can move in the new direction
	if (newDirection == right) {
		newX += velocity;
	}
	if (newDirection == up) {
		newY -= velocity;
	}
	if (newDirection == left) {
		newX -= velocity;
	}
	if (newDirection == down) {
		newY += velocity;
	}
	// If can move in the new direction, then do
	if (CanMove(newX, newY, newDirection, maze)) {
		x = newX;
		y = newY;
		currentDirection = newDirection;
	}
	// Else check if you can keep moving in the current direction
	else
	{
		newX = x, newY = y;
		if (currentDirection == right) {
			newX += velocity;
		}
		if (currentDirection == up) {
			newY -= velocity;
		}
		if (currentDirection == left) {
			newX -= velocity;
		}
		if (currentDirection == down) {
			newY += velocity;
		}
		// If can keep moving in the current direction, then do
		if (CanMove(newX, newY, currentDirection, maze)) {
			x = newX;
			y = newY;
		}
	}
}

bool Pacman::CanMove(float x, float y, Direction direction, Maze maze)
{
	float errorFactor = 0.99 * TILE_SIZE;

	// Checking to see if the new positon each vertex of Pacman rect are in a valid path
	if (maze.IsPath(x, y) && maze.IsPath(x + errorFactor, y) && maze.IsPath(x, y + errorFactor) && maze.IsPath(x + errorFactor, y + errorFactor)) {
		return true;
	}

	return false;
}

void Pacman::Draw()
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
	SDL_Rect rect = { x - 8, y - 8, TILE_SIZE + 2 * 8, TILE_SIZE + 2 * 8 };
	SDL_RenderFillRect(renderer, &rect);
}

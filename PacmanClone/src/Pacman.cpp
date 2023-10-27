#include <SDL2/SDL_image.h>

#include <iostream>

#include "Pacman.h"

Pacman::Pacman()
{
}

Pacman::Pacman(SDL_Renderer* renderer)
	:x(20 * 14), y(20 * 23), renderer(renderer)
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


	frameHeight = 32;
	frameWidth = 32;
	currentFrame = 0;
	maxFrame = 5;
	animationSpeed = 50;
	lastFrameChangeTime = SDL_GetTicks();
}

void Pacman::HandleInput(SDL_Keycode key)
{
	if (key == SDLK_w || key == SDLK_UP) {
		newDirection = up;
	}
	if (key == SDLK_a || key == SDLK_LEFT) {
		newDirection = left;
	}
	if (key == SDLK_s || key == SDLK_DOWN) {
		newDirection = down;
	}
	if (key == SDLK_d || key == SDLK_RIGHT) {
		newDirection = right;
	}
}

void Pacman::Update(Maze& maze)
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
	// If sprite can move in the new direction, then do
	if (CanMove(newX, newY, maze)) {
		x = newX;
		y = newY;
		currentDirection = newDirection;
		isMoving = true;
		if (maze.IsFood(newX, newY)) {
			maze.ConsumeFood(newX, newY);
		}
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
		// If sprite can keep moving in the current direction, then do
		if (CanMove(newX, newY, maze)) {
			x = newX;
			y = newY;
			if (maze.IsFood(newX, newY)) {
				maze.ConsumeFood(newX, newY);
			}
		}
		else {
			isMoving = false;
		}
	}

	if (isMoving) {
		// Calculate time since the last frame change of the sprite animation
		Uint32 currentTime = SDL_GetTicks();
		Uint32 elapsedTime = currentTime - lastFrameChangeTime;

		if (elapsedTime >= animationSpeed) {
			// Update the current frame of animation if enough time has passed
			currentFrame = (currentFrame + 1) % maxFrame;
			lastFrameChangeTime = SDL_GetTicks();
		}
	}
}

bool Pacman::CanMove(float x, float y, Maze& maze)
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
	// The part of the sprite sheet texture that gets output
	SDL_Rect srcRect = { currentFrame * frameWidth, currentDirection * frameHeight, frameWidth, frameHeight };
	// The actual place in the window where the sprite frame is rendered
	SDL_Rect dstRect = { x - 8, y - 8, TILE_SIZE + 2 * 8, TILE_SIZE + 2 * 8 };
	SDL_RenderCopy(renderer, texture, &srcRect, &dstRect);
}

#pragma once

#include <SDL2/SDL.h>

#include "Constants.h"
#include "Maze.h"

class Pacman {
public:
	Pacman();
	Pacman(SDL_Renderer* renderer);
	void HandleInput(SDL_Keycode key);
	void Update(Maze& maze);
	bool CanMove(float x, float y, Maze& maze);
	void Draw();
public:
	int x, y;
	int velocity = 1;
	Direction currentDirection;
	Direction newDirection;
	bool isMoving = true; // Primarily used for the sprite animation

	SDL_Renderer* renderer;
	SDL_Texture* texture;

	int frameWidth; // Width of each frame in sprite sheet
	int frameHeight; // Height of each frame in sprite sheet
	int currentFrame;
	int maxFrame; // Total frame per animation
	int animationSpeed; // Speed at which frames change (in milliseconds)
	Uint32 lastFrameChangeTime; // Time when the last frame change occurred


};

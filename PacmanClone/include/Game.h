#pragma once

#include <SDL2/SDL.h>

#include <string>

#include "Constants.h"
#include "Maze.h"
#include "Pacman.h"
#include "Ghost.h"
#include "Blinky.h"
#include "Inky.h"
#include "Pinky.h"
#include "BottomHUD.h"

class Game {
public:
	Game();
	~Game();
	void Run();
	void HandleEvents();
	void Update();
	void Render();

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	std::string title = "PacMan Clone";
	
	int delayTime = 1000 / targetFps;
	bool running = true;

	Maze maze;
	Pacman pacman;
	Blinky blinky;

	Inky inky;
	Pinky pinky;
};

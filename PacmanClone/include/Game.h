#pragma once

#include <SDL2/SDL.h>

#include <string>

#include "Constants.h"

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
	std::string title = "PacMac Clone";
	
	int delayTime = 1000 / targetFps;

	bool running = true;
};

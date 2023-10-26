#pragma once

#include <SDL2/SDL.h>

#include <vector>
#include <string>

class Maze {
public:
	Maze();
	Maze(SDL_Renderer* renderer);
	void Draw();
	bool IsPath(int x, int y);
private:
	std::vector<std::string> layout;
	int tileSize;
	SDL_Renderer* renderer;

	SDL_Texture* texture;
};
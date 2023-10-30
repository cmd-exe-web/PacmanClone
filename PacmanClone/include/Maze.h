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
	bool IsFood(int x, int y);
	bool IsIntersection(int x, int y);
	void ConsumeFood(int x, int y);
	bool isOpen;
private:
	std::vector<std::string> layout;
	int tileSize;
	SDL_Renderer* renderer;

	SDL_Texture* texture;
};

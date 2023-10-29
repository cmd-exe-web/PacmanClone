#include <iostream>

#include "Maze.h"
#include "Constants.h"

Maze::Maze()
{
}

Maze::Maze(SDL_Renderer* renderer)
	:renderer(renderer)
{
	layout = {
	"2000000000000320000000000003",
	"1............11............1",
	"1.2003.20003.11.20003.2003.1",
	"1o1  1.1   1.11.1   1.1  1o1",
	"1.4005.40005.45.40005.4005.1",
	"1..........................1",
	"1.2003.23.20000003.23.2003.1",
	"1.4005.11.40032005.11.4005.1",
	"1......11....11....11......1",
	"400003.14003 11 20051.200005",
	"     1.12005 45 40031.1     ",
	"     1.11          11.1     ",
	"     1.11 20099003 11.1     ",
	"000005.45 1      1 45.400000",
	"      .   1      1   .      ",
	"000003.23 1      1 23.200000",
	"     1.11 40000005 11.1     ",
	"     1.11          11.1     ",
	"     1.11 20000003 11.1     ",
	"200005.45 40032005 45.400003",
	"1............11............1",
	"1.2003.20003.11.20003.2003.1",
	"1.4031.40005.45.40005.1205.1",
	"1o..11................11..o1",
	"403.11.23.20000003.23.11.205",
	"205.45.11.40032005.11.45.403",
	"1......11....11....11......1",
	"1.2000054003.11.2005400003.1",
	"1.4000000005.45.4000000005.1",
	"1..........................1",
	"4000000000000000000000000005"
	};
	tileSize = TILE_SIZE;

	SDL_Surface* surface = SDL_LoadBMP("assets/images/pacman-maze-4.bmp");
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

void Maze::Draw()
{
	for (int i = 0; i < layout.size(); i++) {
		for (int j = 0; j < layout[0].size(); j++) {
			SDL_Rect dstRect = { j * tileSize, i * tileSize, tileSize, tileSize };
			SDL_Rect srcRect;
			if (layout[i][j] == '0') {
				srcRect = { 20 * 0, 20 * 0, 20, 20 };
			}
			if (layout[i][j] == '1') {
				srcRect = { 20 * 1, 20 * 0, 20, 20 };
			}
			if (layout[i][j] == '2') {
				srcRect = { 20 * 2, 20 * 0, 20, 20 };
			}
			if (layout[i][j] == '3') {
				srcRect = { 20 * 3, 20 * 0, 20, 20 };
			}
			if (layout[i][j] == '4') {
				srcRect = { 20 * 0, 20 * 1, 20, 20 };
			}
			if (layout[i][j] == '5') {
				srcRect = { 20 * 1, 20 * 1, 20, 20 };
			}
			if (layout[i][j] == '9') {
				srcRect = { 20 * 0, 20 * 2, 20, 20 };
			}
			if (layout[i][j] == '.') {
				srcRect = { 20 * 2, 20 * 1, 20, 20 };
			}
			if (layout[i][j] == 'o') {
				srcRect = { 20 * 3, 20 * 1, 20, 20 };
			}
			if (layout[i][j] == ' ') {
				srcRect = { 20 * 1, 20 * 3, 20, 20 };
			}

			SDL_RenderCopy(renderer, texture, &srcRect, &dstRect);
		}
	}
}

bool Maze::IsPath(int x, int y)
{
	if (x < 0 || y < 0 || x > MAZE_WIDTH || y > MAZE_HEIGHT) {
		return false;
	}

	int indexX = x / tileSize;
	int indexY = y / tileSize;

	char ch = layout[indexY][indexX];
	return (ch == ' ' || ch == '.' || ch == 'o');
}

bool Maze::IsFood(int x, int y)
{
	int indexX = x / tileSize;
	int indexY = y / tileSize;

	return layout[indexY][indexX] == '.';
}

bool Maze::IsIntersection(int x, int y)
{
	int walkableNeighbour = 0;
	if (IsPath(x + tileSize, y))walkableNeighbour++;
	if (IsPath(x - tileSize, y))walkableNeighbour++;
	if (IsPath(x, y + tileSize))walkableNeighbour++;
	if (IsPath(x, y - tileSize))walkableNeighbour++;

	if (walkableNeighbour > 2)
		return true;
	else
		return false;
}

void Maze::ConsumeFood(int x, int y)
{
	int indexX = x / tileSize;
	int indexY = y / tileSize;
	
	layout[indexY][indexX] = ' ';
	score += 10;
}

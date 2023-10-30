#include "Ghost.h"

#include <SDL2/SDL_image.h>

#include <iostream>
#include <random>

Ghost::Ghost()
{
}

Ghost::Ghost(SDL_Renderer* renderer)
	:x(15 * TILE_SIZE), y(11 * TILE_SIZE), currentDirection(Right), renderer(renderer)
{
	SDL_Surface* surface = IMG_Load("assets/images/pacman-ghosts-sprite.png");
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
	frameHeight = 160;
	frameWidth = 160;

	currentMode = Mode::Chase;
}

void Ghost::Update(Maze& maze, Pacman& pacman)
{
}

void Ghost::ChaseTarget(SDL_Point target, Maze& maze)
{
	int newX = x, newY = y;
	if (currentDirection == Right) {
		newX += velocity;
	}
	if (currentDirection == Left) {
		newX -= velocity;
	}
	if (currentDirection == Up) {
		newY -= velocity;
	}
	if (currentDirection == Down) {
		newY += velocity;
	}

	// Check warping through tunnels is possible
	if (newX + TILE_SIZE > MAZE_WIDTH) {
		x = 0;
	}
	else if (newX < 0) {
		x = MAZE_WIDTH - TILE_SIZE;
	}
	// Else check if its coinciding with a intersection or a dead-end turn
	else if (!CanMove(newX, newY, maze) || CoincidesIntersection(x, y, maze)) {
		auto closestPaths = ClosestPath({ target.x, target.y });
		std::vector<Direction> availableDirections = TurnsAvailable(maze);

		Direction reverseDirection = GetReverseDirection(currentDirection);

		auto it = std::find(availableDirections.begin(), availableDirections.end(), reverseDirection);
		if (it != availableDirections.end()) {
			availableDirections.erase(it);
		}

		for (int i = 0; i < closestPaths.size(); i++) {
			if (std::find(availableDirections.begin(), availableDirections.end(), closestPaths[i]) == availableDirections.end()) {
				closestPaths.erase(closestPaths.begin() + i);
				i--;
			}
		}

		Direction newDirection = closestPaths[0];

		if (newDirection == Right) {
			x += velocity;
		}
		if (newDirection == Up) {
			y -= velocity;
		}
		if (newDirection == Left) {
			x -= velocity;
		}
		if (newDirection == Down) {
			y += velocity;
		}
		currentDirection = newDirection;
	}
	// Else continue to move in current path
	else {
		x = newX;
		y = newY;
	}
}

Direction Ghost::GetReverseDirection(Direction direction)
{	
	if (direction == Right) return Left;
	else if (direction == Left) return Right;
	else if (direction == Up) return Down;
	else return Up;
}

void Ghost::MoveRandomly(Maze& maze)
{
	int newX = x, newY = y;

	if (currentDirection == Right) {
		newX += velocity;
	}
	if (currentDirection == Left) {
		newX -= velocity;
	}
	if (currentDirection == Up) {
		newY -= velocity;
	}
	if (currentDirection == Down) {
		newY += velocity;
	}

	// Check if warpping is possible
	if (newX + TILE_SIZE >= MAZE_WIDTH) {
		x = 0;
	}
	else if (newX < 0) {
		x = MAZE_WIDTH - TILE_SIZE;
	}
	// If not, continue with regular movement
	else
	{
		if (CanMove(newX, newY, maze) && !CoincidesIntersection(x, y, maze))
		{
			x = newX;
			y = newY;
		}
		else {
			std::vector<Direction> turnsAvailable = TurnsAvailable(maze);

			Direction reverseDirection = GetReverseDirection(currentDirection);

			auto it = std::find(turnsAvailable.begin(), turnsAvailable.end(), reverseDirection);
			if (it != turnsAvailable.end()) {
				turnsAvailable.erase(it);
			}
			int availableDirections = turnsAvailable.size();

			Direction newDirection;

			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> dist(0, availableDirections - 1);

			int randomDirection = dist(gen);
			newDirection = turnsAvailable[randomDirection];

			if (newDirection == Right) {
				x += velocity;
			}
			if (newDirection == Up) {
				y -= velocity;
			}
			if (newDirection == Left) {
				x -= velocity;
			}
			if (newDirection == Down) {
				y += velocity;
			}
			currentDirection = newDirection;
		}
	}
}

std::vector<Direction> Ghost::TurnsAvailable(Maze& maze)
{
	std::vector<Direction> turnsAvailable;

	float errorFactor = 0.001 * TILE_SIZE;

	float left = x - errorFactor;
	float right = x + TILE_SIZE + errorFactor;
	float up = y - errorFactor;
	float down = y + TILE_SIZE + errorFactor;

	if (maze.IsPath(left, y)) {
		// Check if all four vertex are not colliding with a wall
		if (maze.IsPath(left, y + TILE_SIZE - errorFactor) && maze.IsPath(left + TILE_SIZE - errorFactor, y) && maze.IsPath(left + TILE_SIZE - errorFactor, y + TILE_SIZE - errorFactor)) {
			turnsAvailable.push_back(Left);
		}
	}
	if (maze.IsPath(right, y)) {
		if (maze.IsPath(right, y + TILE_SIZE - errorFactor) && maze.IsPath(right - TILE_SIZE, y) && maze.IsPath(right - TILE_SIZE, y + TILE_SIZE - errorFactor)) {
			turnsAvailable.push_back(Right);
		}
	}
	if (maze.IsPath(x, up)) {
		if (maze.IsPath(x + TILE_SIZE - errorFactor, up) && maze.IsPath(x, up - TILE_SIZE) && maze.IsPath(x + TILE_SIZE - errorFactor, up - TILE_SIZE)) {
			turnsAvailable.push_back(Up);
		}
	}
	if (maze.IsPath(x, down)) {
		if (maze.IsPath(x + TILE_SIZE - errorFactor, down) && maze.IsPath(x, down - TILE_SIZE) && maze.IsPath(x + TILE_SIZE - errorFactor, down - TILE_SIZE)) {
			turnsAvailable.push_back(Down);
		}
	}

	return turnsAvailable;
}

bool Ghost::CanMove(float x, float y, Maze maze)
{
	float errorFactor = 0.9999 * TILE_SIZE;
	if (maze.IsPath(x, y) && maze.IsPath(x + errorFactor, y) && maze.IsPath(x, y + errorFactor) && maze.IsPath(x + errorFactor, y + errorFactor)) {
		return true;
	}
	return false;
}


bool Ghost::CoincidesIntersection(float x, float y, Maze& maze)
{
	float errorFactor = 0.9999 * TILE_SIZE;

	if (maze.IsIntersection(x, y) && maze.IsIntersection(x + errorFactor, y) && maze.IsIntersection(x, y + errorFactor) && maze.IsIntersection(x + errorFactor, y + errorFactor)) {
		return true;
	}
	return false;
}

void Ghost::SetTarget(SDL_Point target)
{
	currentTarget = target;
}

std::vector<Direction> Ghost::ClosestPath(SDL_Point target)
{
	std::vector<std::pair<int, Direction>> distances;
	distances.push_back({ GetDistance({ x, y - TILE_SIZE }, target), Up });
	distances.push_back({ GetDistance({ x - TILE_SIZE, y }, target), Left });
	distances.push_back({ GetDistance({ x, y + TILE_SIZE }, target), Down });
	distances.push_back({ GetDistance({ x + TILE_SIZE, y }, target), Right });

	std::sort(distances.begin(), distances.end());

	std::vector<Direction> sortedDirections(4);

	for (int i = 0; i < 4; i++) {
		sortedDirections[i] = distances[i].second;
	}

	return sortedDirections;
}


float Ghost::GetDistance(SDL_Point point1, SDL_Point point2)
{
	// Note: Manahattan Distance doesn't work, USE STRAIGHT LINE DISTANCE ONLY
	return abs(pow(point1.x, 2) - pow(point2.x, 2)) + abs(pow(point1.y, 2) - pow(point2.y, 2));
}

void Ghost::Draw()
{
	SDL_Rect srcRect = { (int)ghostType * frameWidth, currentDirection * frameHeight, frameWidth, frameHeight };
	SDL_Rect dstRect = { x - 8, y - 8, TILE_SIZE + 2 * 8, TILE_SIZE + 2 * 8 };
	SDL_RenderCopy(renderer, texture, &srcRect, &dstRect);
}

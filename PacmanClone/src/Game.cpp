#include "Game.h"

#include <iostream>

Game::Game()
{
	SDL_Init(SDL_INIT_VIDEO);

	// Create a window
	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		std::cerr << "SDL_CreateWindow failed. Error: " << SDL_GetError() << std::endl;
		exit(EXIT_FAILURE);
	}
	// Create a renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr) {
		std::cerr << "SDL_CreateRenderer failed. Error: " << SDL_GetError() << std::endl;
		exit(EXIT_FAILURE);
	}
}

Game::~Game()
{	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

void Game::Run()
{
	Uint32 startTime;

	while (running) {
		startTime = SDL_GetTicks();
	
		HandleEvents();
		Update();
		Render();

		Uint32 frameTime = SDL_GetTicks() - startTime;
		if (frameTime < delayTime) {
			SDL_Delay(delayTime - frameTime);
		}
	}
}

void Game::HandleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0) {
		if (event.type == SDL_QUIT) {
			running = false;
			break;
		}
	}
}

void Game::Update()
{
}

void Game::Render()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	//Stuff to Draw

	SDL_RenderPresent(renderer);
}

#include "BottomHUD.h"
#include "Constants.h"

#include <iostream>
#include <string>

BottomHUD::BottomHUD()
{
}

BottomHUD::BottomHUD(SDL_Renderer* renderer)
	:renderer(renderer)
{
	if (TTF_Init() == -1) {
		std::cerr << "Couldn't Initialize SDL_ttf. Error: " << TTF_GetError() << std::endl;
		exit(EXIT_FAILURE);
	}
	font = TTF_OpenFont("assets/fonts/PressStart2P-Regular.ttf", 100);
	if (font == nullptr) {
		std::cerr << "Couldn't open the font. Error: " << TTF_GetError() << std::endl;
		exit(EXIT_FAILURE);
	}
	scoreColor = { 255, 255, 255, 255 };
}

void BottomHUD::Draw()
{
	std::string scoreText = "Score: " + std::to_string(score);
	SDL_Surface* surface = TTF_RenderText_Solid(font, scoreText.c_str(), scoreColor);
	SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	SDL_Rect dstRect1 = { 10, MAZE_HEIGHT + 5, 150, 25 };
	SDL_RenderCopy(renderer, scoreTexture, NULL, &dstRect1);
}

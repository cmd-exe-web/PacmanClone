#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class BottomHUD {
public:
	BottomHUD();
	BottomHUD(SDL_Renderer* renderer);
	void Draw();
private:
	SDL_Renderer* renderer;
	TTF_Font* font;
	SDL_Color scoreColor;
};

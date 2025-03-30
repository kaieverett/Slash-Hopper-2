#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include "Structures.h"

SDL_Texture* loadTexture(const char* path, SDL_Renderer* renderer);
SDL_Texture* createTextTexture(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, const SDL_Color& color);
void updateUITextures(SDL_Renderer* renderer, UI& ui, Player& player);
bool initSDL(SDL_Window*& window, SDL_Renderer*& renderer);
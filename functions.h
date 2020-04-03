#pragma once

SDL_Texture * loadTexture(SDL_Renderer * renderTarget, std::string filePath);

void sdlQuit(SDL_Window * window, SDL_Renderer * renderTarget);

bool isCollide(SDL_Rect rectOne, SDL_Rect rectTwo);

void beginGame(SDL_Window * window, SDL_Renderer * renderTarget);

void playGame(SDL_Window * window, SDL_Renderer * renderTarget);

bool endGame(SDL_Window * window, SDL_Renderer * renderTarget);
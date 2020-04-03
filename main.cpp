#include<bits/stdc++.h>
#include<SDL_image.h>
#include<SDL.h>
#include "SDL_Main.h"

#include "functions.h"

int main(int argc, char *argv[]){
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF);
    srand(time(NULL));

    int windowHeight=300, windowWidth=600;
    std::string windowName="NyancatJMP";
    std::string windowIcon_url="./images/icon.png";

    SDL_Window * window = nullptr;
    SDL_Renderer * renderTarget = nullptr;

    window = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, 0);
    renderTarget = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_Surface * surface = IMG_Load(windowIcon_url.c_str());
    SDL_SetWindowIcon(window, surface);
    SDL_FreeSurface(surface);

    beginGame(window, renderTarget);
    while(true){
        playGame(window, renderTarget);
        if(endGame(window, renderTarget)) break;
    }

    // SDL_Delay(2000);

    sdlQuit(window, renderTarget);
    return 0;
}

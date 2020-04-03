#include<bits/stdc++.h>
#include<SDL_image.h>
#include<SDL.h>

#include "Menu.h"
#include "functions.h"

Menu::Menu(SDL_Renderer * renderTarget){
    
    texture = loadTexture(renderTarget, filePath);

    // Assign texture's size to cropRect
    SDL_QueryTexture(texture, 0, 0, &cropRect.w, &cropRect.h);

    cropRect.x = 0;
    cropRect.y = 0;

    positionRect.x = 0;
    positionRect.y = 0;
    positionRect.w = cropRect.w;
    positionRect.h = cropRect.h;
}

Menu::~Menu(){
    SDL_DestroyTexture(texture);
    // texture = nullptr;
}

void Menu::Draw(SDL_Renderer * renderTarget){
    SDL_RenderCopy(renderTarget, texture, &cropRect, &positionRect);
}

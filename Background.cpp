#include<bits/stdc++.h>
#include<SDL_image.h>
#include<SDL.h>

#include "Background.h"
#include "functions.h"

Background::Background(SDL_Renderer * renderTarget){
    
    texture = loadTexture(renderTarget, filePath);

    // Assign texture's size to cropRect
    SDL_QueryTexture(texture, 0, 0, &cropRect.w, &cropRect.h);
    // I made the background doubled in length so that it'd be easier to process

    cropRect.w /= 2;
    cropRect.x = 0;
    cropRect.y = 0;

    positionRect.x = 0;
    positionRect.y = 0;
    positionRect.w = cropRect.w;
    positionRect.h = cropRect.h;
}

Background::~Background(){ 
    SDL_DestroyTexture(texture);
    // texture = nullptr;
} 

void Background::Update(float dTime){
    cropRect.x += round(dTime * scrollSpd);
    cropRect.x %= cropRect.w;
}

void Background::Draw(SDL_Renderer * renderTarget){
    SDL_RenderCopy(renderTarget, texture, &cropRect, &positionRect);
}

void Background::setScrollSpeed(float v){
    scrollSpd = v;
}

float Background::getScrollSpeed(){
    return scrollSpd;
}

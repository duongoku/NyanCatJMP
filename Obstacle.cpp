#include<bits/stdc++.h>
#include<SDL_image.h>
#include<SDL.h>

#include "Obstacle.h"
#include "functions.h"

Obstacle::Obstacle(SDL_Renderer * renderTarget){
    filePath[18] = ('0' + (rand() % 4));

    texture = loadTexture(renderTarget, filePath);

    SDL_QueryTexture(texture, 0, 0, &cropRect.w, &cropRect.h);
    cropRect.x = 0;
    cropRect.y = 0;
    positionRect.w = cropRect.w;
    positionRect.h = cropRect.h;
    positionRect.x = 0;
    // positionRect.x = rand()%500;
    positionRect.y = distToGround - cropRect.h;
}
Obstacle::~Obstacle(){
    SDL_DestroyTexture(texture);
    // texture = nullptr;
}

void Obstacle::setNewTexture(SDL_Renderer * renderTarget){
    filePath[18] = ('0' + (rand() % 4));

    texture = loadTexture(renderTarget, filePath);

    SDL_QueryTexture(texture, 0, 0, &cropRect.w, &cropRect.h);

    positionRect.w = cropRect.w;
    positionRect.h = cropRect.h;
    positionRect.y = distToGround - cropRect.h;
}

void Obstacle::setX(int x){
    positionRect.x = x;
}

int Obstacle::getX(){
    return positionRect.x;
}

int Obstacle::getW(){
    return cropRect.w;
}

void Obstacle::Update(float dTime){
    positionRect.x -= round(dTime * scrollSpd);
}

void Obstacle::Draw(SDL_Renderer * renderTarget){
    SDL_RenderCopy(renderTarget, texture, &cropRect, &positionRect);
}

SDL_Rect Obstacle::getRect(){
    return positionRect;
}

void Obstacle::setScrollSpeed(float v){
    scrollSpd = v;
}

float Obstacle::getScrollSpeed(){
    return scrollSpd;
}
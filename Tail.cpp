#include<bits/stdc++.h>
#include<SDL_image.h>
#include<SDL.h>

#include "Tail.h"
#include "functions.h"

Tail::Tail(SDL_Renderer * renderTarget){

	texture = loadTexture(renderTarget, filePath);

	SDL_QueryTexture(texture, 0, 0, &cropRect.w, &cropRect.h);
	// I made it doubled in length like the background so that it'd be
	// easier to deal with.
	maxW=cropRect.w/2;
	cropRect.w=startW;
	cropRect.x=0;
	cropRect.y=0;

	positionRect.w=cropRect.w;
	positionRect.h=cropRect.h;
}

Tail::~Tail(){
	SDL_DestroyTexture(texture);
}

void Tail::Update(float dTime){
    cropRect.x += round(dTime * scrollSpd);
    cropRect.x %= maxW;
}

void Tail::Draw(SDL_Renderer * renderTarget){
	SDL_RenderCopy(renderTarget, texture, &cropRect, &positionRect);
}

void Tail::setX(int x){
	positionRect.x=x;
}

void Tail::setY(int y){
	y+=offsetY;
	positionRect.y=y;
}

void Tail::icrW(){
	cropRect.w+=minW;
	if(cropRect.w>maxW) cropRect.w=maxW;
	positionRect.w=cropRect.w;
}

SDL_Rect Tail::getRect(){
	return positionRect;
}
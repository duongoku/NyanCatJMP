#include<bits/stdc++.h>
#include<SDL_image.h>
#include<SDL.h>

#include "Snumber.h"
#include "functions.h"

SNumber::SNumber(SDL_Renderer * renderTarget){

    texture = loadTexture(renderTarget, filePath);

    SDL_QueryTexture(texture, 0, 0, &cropRect.w, &cropRect.h);
    // There are 10 digits in the texture lol
    cropRect.w /= 10;
    positionRect.w = cropRect.w;
    positionRect.h = cropRect.h;

    cropRect.x = 0;
    cropRect.y = 0;
    positionRect.x = init_x;
    positionRect.y = init_y;
}

SNumber::~SNumber(){
    SDL_DestroyTexture(texture);
    // texture = nullptr;
}

void SNumber::Draw(int x, SDL_Renderer * renderTarget){

    // SDL_RenderCopy(renderTarget, texture, &cropRect, &positionRect);
    // ten zeros
    std::string playerScore = "0000000000";
    unsigned tmp=playerScore.size()-1;
    while(x>0){
        if(tmp<0) break;
        playerScore[tmp] = (x%10 + '0');
        x/=10;
        tmp--;
    }
    for(tmp=0; tmp < playerScore.size(); tmp++){
        positionRect.x = init_x + tmp * cropRect.w;
        cropRect.x = (playerScore[tmp]-'0') * cropRect.w;
        SDL_RenderCopy(renderTarget, texture, &cropRect, &positionRect);
    }
}

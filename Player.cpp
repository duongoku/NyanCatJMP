#include<bits/stdc++.h>
#include<SDL_image.h>
#include<SDL.h>

#include "Player.h"
#include "functions.h"

Player::Player(SDL_Renderer * renderTarget){
    
    texture = loadTexture(renderTarget, filePath);

    SDL_QueryTexture(texture, NULL, NULL, &cropRect.w, &cropRect.h);
    cropRect.w /= total_frame;
    positionRect.x = playerInitX;
    positionRect.y = playerInitY;
    ground = playerInitY;
    positionRect.w = cropRect.w;
    positionRect.h = cropRect.h;
    cropRect.x = cropRect.w/total_frame;
    cropRect.y = 0;

    //Body
    hitRect[0].x=14;
    hitRect[0].y=2;
    hitRect[0].w=44;
    hitRect[0].h=40;
    //Head
    hitRect[1].x=34;
    hitRect[1].y=10;
    hitRect[1].w=34;
    hitRect[1].h=28;
}

Player::~Player(){
    SDL_DestroyTexture(texture);
    // texture = nullptr;
}

void Player::setJumpSpd(){
    if(positionRect.y == ground) upSpd = jumpSpd;
}

void Player::Update(float dTime){
    positionRect.x += (int)round(dTime * moveSpd);
    positionRect.x %= 600;
    if(positionRect.y <= ground){
        positionRect.y -= (int)round(dTime * upSpd);
        upSpd-=downAcc*dTime;
    }
    if(positionRect.y >= ground){
        positionRect.y = ground;
        upSpd = 0;
    }
    cropRect.x = (int)frame_cnt*cropRect.w;
    frame_cnt += frame_spd;
    if((int)frame_cnt >= total_frame) frame_cnt = 0;
}

void Player::Draw(SDL_Renderer * renderTarget){
    SDL_RenderCopy(renderTarget, texture, &cropRect, &positionRect);
}

SDL_Rect Player::getRect(){
    return positionRect;
}

int Player::getHitNum(){
    return hitboxes;
}

SDL_Rect Player::getHitBox(int id){
    return hitRect[id];
}
#include<bits/stdc++.h>
#include<SDL_image.h>
#include<SDL.h>

#include "functions.h"

#include "Player.h"
#include "Background.h"
#include "Menu.h"
#include "Obstacle.h"
#include "Snumber.h"
#include "Tail.h"

SDL_Texture * loadTexture(SDL_Renderer * renderTarget, std::string filePath){
    SDL_Surface * surface = IMG_Load(filePath.c_str());
    SDL_Texture * texture;
    if(surface == NULL) std::cout<<IMG_GetError()<<std::endl;
    else{
        texture = SDL_CreateTextureFromSurface(renderTarget, surface);
        if(texture == NULL) std::cout<<SDL_GetError()<<std::endl;
    }
    SDL_FreeSurface(surface);
    return texture;
}


void sdlQuit(SDL_Window * window, SDL_Renderer * renderTarget){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderTarget);
    // window = nullptr;
    // renderTarget = nullptr;
    SDL_Quit();
    IMG_Quit();
    std::exit(0);
}

//I thought we don't have builtin function for that lol so I did one
//but I found SDL_HasIntersection() lol
bool isCollide(SDL_Rect rectOne, SDL_Rect rectTwo){
    // static int offset = 5;
    if(((rectOne.x < rectTwo.x + rectTwo.w) && (rectOne.x > rectTwo.x))||
       ((rectTwo.x < rectOne.x + rectOne.w) && (rectTwo.x > rectOne.x))){
        if(((rectOne.y < rectTwo.y + rectTwo.h) && (rectOne.y > rectTwo.y))||
           ((rectTwo.y < rectOne.y + rectOne.h) && (rectTwo.y > rectOne.y))) return true;
    }
    return false;
}

void beginGame(SDL_Window * window, SDL_Renderer * renderTarget){
    // int windowHeight=300, windowWidth=600;
    float currTime=SDL_GetTicks(), prevTime, deltaTime;
    const Uint8 *keyState;
    SDL_Event ev;

    Background bg1(renderTarget);
    bg1.setScrollSpeed(0.1);
    Menu mn1(renderTarget);

    while(true){
        if(SDL_PollEvent(&ev) != 0) if(ev.type == SDL_QUIT) sdlQuit(window, renderTarget);
        keyState=SDL_GetKeyboardState(NULL);
        if(keyState[SDL_SCANCODE_SPACE] || keyState[SDL_SCANCODE_UP] || ev.type == SDL_MOUSEBUTTONDOWN) break;

        prevTime=currTime;
        currTime=SDL_GetTicks();
        deltaTime=(currTime-prevTime)*1.0f;

        bg1.Update(deltaTime);
        SDL_RenderClear(renderTarget);
        bg1.Draw(renderTarget);
        mn1.Draw(renderTarget);
        SDL_RenderPresent(renderTarget);
    }
}

void playGame(SDL_Window * window, SDL_Renderer * renderTarget){
    int obsWidth, mxdist=400, mndist=300;
    // int windowHeight=300;
    int windowWidth=600;
    int tmpNum;
    float scrollAcc=0.015;
    float currTime=SDL_GetTicks(), prevTime, deltaTime;
    float plrScore=0;
    int scoreThreshold=2500, tempScore=0;
    const Uint8 *keyState;
    bool actionLoop=true;
    SDL_Event ev;
    SDL_Rect tmpRect;
    int totalObs = 16, obsChunk = 3;

    Player p1(renderTarget);
    Tail tl1(renderTarget);
    Background bg1(renderTarget);
    Obstacle obs[25](renderTarget);
    obsWidth = obs[0].getW();
    SNumber sn(renderTarget);

    obs[0].setX((rand()%windowWidth) + windowWidth);

    for(int i=1;i<totalObs;i++){
        obs[i].setX(obs[i-1].getX()+(rand()%(mxdist-mndist+1)+mndist)*(1+obs[i].getScrollSpeed()));
        //startoff with no chunks so that it'd be easier to pass
        // tmpNum=rand()%obsChunk;
        // for(int j=0;(j<tmpNum)&&(i<15);j++){
        //     i++;
        //     obs[i].setX(obs[i-1].getX()+obsWidth);
        // }
    }

    while(actionLoop){
        // SDL_PumpEvents();
        if(SDL_PollEvent(&ev) != 0){
            if(ev.type == SDL_QUIT) sdlQuit(window, renderTarget);

            if(ev.type == SDL_MOUSEBUTTONDOWN){
                // std::cout<<"Mouse clicked at: "<<ev.button.x<<" "<<ev.button.y<<std::endl;
                p1.setJumpSpd();
            }
        }

        prevTime=currTime;
        currTime=SDL_GetTicks();
        deltaTime=(currTime-prevTime)*1.0f;

        plrScore+=deltaTime;
        tempScore+=deltaTime;
        if(tempScore>scoreThreshold){
            tempScore=0;
            bg1.setScrollSpeed(bg1.getScrollSpeed()+scrollAcc);
            for(int id=0;id<totalObs;id++){
                obs[id].setScrollSpeed(bg1.getScrollSpeed());
            }
            tl1.icrW();
        }

        keyState=SDL_GetKeyboardState(NULL);

        if(keyState[SDL_SCANCODE_SPACE] || keyState[SDL_SCANCODE_UP]){
                p1.setJumpSpd();
        }

        bg1.Update(deltaTime);
        for(int i=0;i<totalObs;i++) obs[i].Update(deltaTime);
        p1.Update(deltaTime);
        tl1.Update(deltaTime);
        tl1.setY(p1.getRect().y);
        tl1.setX(p1.getRect().x-tl1.getRect().w+p1.getRect().w/3);

        SDL_RenderClear(renderTarget);

        bg1.Draw(renderTarget);
        // we do this from obs[2] to ensure that all chunks of obstacle
        // are out of the screen before the replacement
        if(obs[obsChunk-1].getX()<(-obsWidth)){
            // for(int i=0;i<totalObs;i++){
            //     std::cout<<obs[i].getX()<<" ";
            // }
            // std::cout<<std::endl;
            for(int i=0;i<totalObs-obsChunk;i++){
                obs[i]=obs[i+obsChunk];
            }
            for(int i=totalObs-obsChunk;i<totalObs;i++){
                obs[i].setNewTexture(renderTarget);
                obs[i].setX(obs[i-1].getX()+(rand()%(mxdist-mndist+1)+mndist)*(1+obs[i].getScrollSpeed()));

                tmpNum=rand()%obsChunk;
                for(int j=0;(j<tmpNum)&&(i<totalObs-1);j++){
                    i++;
                    obs[i].setNewTexture(renderTarget);
                    obs[i].setX(obs[i-1].getX()+obsWidth);
                }
            }
            // for(int i=0;i<totalObs;i++){
            //     std::cout<<obs[i].getX()<<" ";
            // }
            // std::cout<<std::endl;
        }
        for(int i=0;i<totalObs;i++){
            tmpNum=p1.getHitNum();
            for(int j=0;j<tmpNum;j++){
                tmpRect = p1.getHitBox(j);
                tmpRect.x += p1.getRect().x;
                tmpRect.y += p1.getRect().y;
                if(isCollide(tmpRect, obs[i].getRect())) actionLoop = false;
            }
            obs[i].Draw(renderTarget);
        }
        tl1.Draw(renderTarget);
        p1.Draw(renderTarget);
        sn.Draw((int)plrScore, renderTarget);

        SDL_RenderPresent(renderTarget);
    }
}

bool endGame(SDL_Window * window, SDL_Renderer * renderTarget){
    std::string uLoseSprite = "./images/uLose.png";
    std::string playAgainSprite = "./images/playAgain_00.png";
    SDL_Texture * texture;
    SDL_Surface * surface;
    SDL_Rect cropRect;
    SDL_Rect positionRect;
    // const Uint8 *keyState;

    surface = IMG_Load(uLoseSprite.c_str());
    texture = SDL_CreateTextureFromSurface(renderTarget, surface);
    SDL_QueryTexture(texture, 0, 0, &cropRect.w, &cropRect.h);
    positionRect.w = cropRect.w;
    positionRect.h = cropRect.h;
    cropRect.x = 0;
    cropRect.y = 0;
    positionRect.x = 0;
    positionRect.y = 0;
    SDL_RenderCopy(renderTarget, texture, &cropRect, &positionRect);

    surface = IMG_Load(playAgainSprite.c_str());
    texture = SDL_CreateTextureFromSurface(renderTarget, surface);
    SDL_QueryTexture(texture, 0, 0, &cropRect.w, &cropRect.h);
    //2 button states in a texture
    cropRect.w/=2;
    positionRect.w = cropRect.w;
    positionRect.h = cropRect.h;
    cropRect.x = 0;
    cropRect.y = 0;
    positionRect.x = 0;
    positionRect.y = cropRect.h * 2;
    SDL_RenderCopy(renderTarget, texture, &cropRect, &positionRect);

    SDL_FreeSurface(surface);
    SDL_RenderPresent(renderTarget);

    SDL_Event ev;
    while(true){
        if(SDL_PollEvent(&ev) != 0){
            if(ev.motion.x > positionRect.x && ev.motion.x < (positionRect.x + positionRect.w) &&
            ev.motion.y > positionRect.y && ev.motion.y < (positionRect.y + positionRect.h)){
                //mouse hovered
                cropRect.x = cropRect.w;
                SDL_RenderCopy(renderTarget, texture, &cropRect, &positionRect);
                SDL_RenderPresent(renderTarget);
            }
            else{
                //mouse not hovered
                cropRect.x = 0;
                SDL_RenderCopy(renderTarget, texture, &cropRect, &positionRect);
                SDL_RenderPresent(renderTarget);
            }
            if(ev.type == SDL_QUIT) sdlQuit(window, renderTarget);
            if(ev.type == SDL_MOUSEBUTTONDOWN){
                if(ev.motion.x > positionRect.x && ev.motion.x < (positionRect.x + positionRect.w) &&
                ev.motion.y > positionRect.y && ev.motion.y < (positionRect.y + positionRect.h)) return false;
            }
        }
    }
    return true;
}

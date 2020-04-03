#pragma once

class Player{
private:
    SDL_Rect positionRect;
    SDL_Rect cropRect;
    //HitRect is offset from (0,0) (positionRect.x, positionRect.y)
    SDL_Rect hitRect[5];
    SDL_Texture * texture;
    std::string filePath = "./images/nyanCat_03.png";
    // float moveSpd=0.3;
    float moveSpd=0;
    float downAcc=0.0035;
    float jumpSpd=1;
    float upSpd=0;
    int playerInitX=50, playerInitY=216;
    float frame_cnt=0, frame_spd=(float)1/3;
    int total_frame=12, hitboxes=2;
    int ground;

public:
    Player(SDL_Renderer * renderTarget);
    ~Player();

    void setJumpSpd();

    void Update(float dTime);

    void Draw(SDL_Renderer * renderTarget);

    SDL_Rect getRect();

    int getHitNum();

    SDL_Rect getHitBox(int id);
};
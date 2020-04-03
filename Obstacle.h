#pragma once

class Obstacle{
private:
    SDL_Rect positionRect;
    SDL_Rect cropRect;
    SDL_Texture * texture;
    std::string filePath = "./images/Obstacle_x.png";
    int distToGround = 260;
    float scrollSpd = 0.45;
public:
    Obstacle(SDL_Renderer * renderTarget);
    ~Obstacle();

    void setNewTexture(SDL_Renderer * renderTarget);

    void setX(int x);

    int getX();

    int getW();

    void Update(float dTime);

    void Draw(SDL_Renderer * renderTarget);

    SDL_Rect getRect();

    void setScrollSpeed(float v);

    float getScrollSpeed();
};

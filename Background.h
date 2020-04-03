#pragma once

class Background{
private:
    SDL_Rect positionRect;
    SDL_Rect cropRect;
    SDL_Texture * texture;
    float scrollSpd = 0.45;
    std::string filePath = "./images/bg.png";
public:
    Background(SDL_Renderer * renderTarget);
    ~Background();

    void Update(float dTime);

    void Draw(SDL_Renderer * renderTarget);

    void setScrollSpeed(float v);

    float getScrollSpeed();
};

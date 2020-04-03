#pragma once

class SNumber{
private:
    SDL_Rect positionRect;
    SDL_Rect cropRect;
    SDL_Texture * texture;
    std::string filePath = "./images/numbers.png";
    int init_x=305, init_y=125;
public:
    SNumber(SDL_Renderer * renderTarget);
    ~SNumber();

    void Draw(int x, SDL_Renderer * renderTarget);
};
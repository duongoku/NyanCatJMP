#pragma once

class Menu{
private:
    SDL_Rect positionRect;
    SDL_Rect cropRect;
    SDL_Texture * texture;
    std::string filePath = "./images/menu.png";
public:
    Menu(SDL_Renderer * renderTarget);
    ~Menu();

    void Draw(SDL_Renderer * renderTarget);
};
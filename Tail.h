#pragma once

class Tail{
private:
    SDL_Rect positionRect;
    SDL_Rect cropRect;
    SDL_Texture * texture;
	std::string filePath = "./images/rainbow.png";
	int maxW, minW=6, startW=minW*5;
	int offsetY=12;
	float scrollSpd=0.15;
	//minW is up to the sprite's style so I must set this manually

public:
	Tail(SDL_Renderer * renderTarget);
	~Tail();

	void setX(int x);
	void setY(int y);
	void icrW();
	SDL_Rect getRect();

	void Update(float dTime);
	void Draw(SDL_Renderer * renderTarget);

};
#pragma once

#include "SDL.h"

class PlatForm
{
public:
	//ÃÊ´ç ÁÂÇ¥ 200
	PlatForm(int createPos, double speed,int type);
	void Update(double timestep_s);

	void setTexturePlatform();
	void renderPlatform(SDL_Renderer* gameRenderer, SDL_Texture* platform_sheet_texture);

	int getx() { return x; }
	int gety() { return y; }
	int getw() { return width; }
	int geth() { return height; }

protected:
	void type0(int createPos);
	void type1(int createPos);

	double velocity;
	int x;
	int y;
	int width;
	int height;

	SDL_Rect platform_source;
	SDL_Rect platform_pos;

};


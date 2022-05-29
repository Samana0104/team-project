#pragma once

#include "SDL.h"
#include "SDL_image.h"

class Obstacle
{
public:
	Obstacle(int createPos,int speed, int type);
	void Update(double timestep_s);

	void setTextureBirds();
	void setTextureGuardRail();
	void setTextureGoal();
	void renderObstacle(SDL_Renderer* gameRenderer, SDL_Texture* obstacle_sheet_texture);

	int getx() { return x; }
	int gety() { return y; }
	int getw() { return width; }
	int geth() { return height; }
	int gettype() { return type; }

protected:
	void type0(int createPos);
	void type1(int createPos);
	void type2(int createPos);
	void type3(int createPos);
	void type4(int createPos);

	SDL_Rect obstacle_source;
	SDL_Rect obstacle_pos;

	int type;
	double velocity;
	int x;
	int y;
	int width;
	int height;

};


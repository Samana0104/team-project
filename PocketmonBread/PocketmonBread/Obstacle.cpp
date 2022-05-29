#pragma once

#include "Obstacle.h"
//#include <iostream>
using namespace std;


Obstacle::Obstacle(int createPos ,int speed,int type)
{
	this->type = type;
	velocity = 200 * (double)speed;
	//일반 가드레일,새
	if (type == 0) {
		type0(createPos);
	}
	else if (type == 1) {
		type1(createPos);
	}
	//추가 발판 가드레일, 새
	else if (type == 2) {
		type2(createPos);
	}
	else if (type == 3) {
		type3(createPos);
	}
	else if (type == 4) {
		type4(createPos);
	}
	else {
		type0(createPos);
	}

}

//가드레일
void
Obstacle::type0(int createPos) {
	x = 50 + 200* createPos;
	y = 550;
	width = 100;
	height = 280;
	setTextureGuardRail();
}

//새떼
void
Obstacle::type1(int createPos) {
	x = 200 * createPos;
	y = 420;
	width = 200;
	height = 250;
	setTextureBirds();
}

//2층
//가드레일
void
Obstacle::type2(int createPos) {
	x = 50 + 200 * createPos;
	y = 150;
	width = 100;
	height = 280;
	setTextureGuardRail();
}

//새떼
void
Obstacle::type3(int createPos) {
	x = 200 * createPos;
	y = 20;
	width = 200;
	height = 250;
	setTextureBirds();
}
//편의점
void
Obstacle::type4(int createPos) {
	x = 200 * createPos + 600;
	y = 500;
	width = 400;
	height = 300;
	setTextureBirds();
}


void
Obstacle::Update(double timestep_s)
{
	double dt = timestep_s;
	x += lround(-velocity * dt);

}

void
Obstacle::setTextureBirds() {

	obstacle_source.x = 3;
	obstacle_source.y = 5;
	obstacle_source.w = 399;
	obstacle_source.h = 370;

	obstacle_pos.x = x;
	obstacle_pos.y = y;
	obstacle_pos.w = width;
	obstacle_pos.h = height;
}

void
Obstacle::setTextureGuardRail() {

	obstacle_source.x = 140;
	obstacle_source.y = 497;
	obstacle_source.w = 167;
	obstacle_source.h = 128;

	obstacle_pos.x = x;
	obstacle_pos.y = y;
	obstacle_pos.w = width;
	obstacle_pos.h = height;
}


void
Obstacle::renderObstacle(SDL_Renderer* gameRenderer, SDL_Texture* obstacle_sheet_texture) {
	obstacle_pos.x = x;
	obstacle_pos.y = y;
	obstacle_pos.w = width;
	obstacle_pos.h = height;

	SDL_RenderCopy(gameRenderer, obstacle_sheet_texture, &obstacle_source, &obstacle_pos);
}



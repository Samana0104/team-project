﻿#pragma once

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
	else {
		type0(createPos);
	}

}

//가드레일
void
Obstacle::type0(int createPos) {
	x = 50 + 200* createPos;
	y = 600;
	width = 100;
	height = 200;
	setTextureGuardRail();
}

//새떼
void
Obstacle::type1(int createPos) {
	x = 200 * createPos;
	y = 400;
	width = 200;
	height = 270;
	setTextureBirds();
}

//2층
//가드레일
void
Obstacle::type2(int createPos) {
	x = 50 + 200 * createPos;
	y = 300;
	width = 100;
	height = 200;
	setTextureGuardRail();
}

//새떼
void
Obstacle::type3(int createPos) {
	x = 200 * createPos;
	y = 100;
	width = 200;
	height = 270;
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

	obstacle_source.x = 550;
	obstacle_source.y = 360;
	obstacle_source.w = 200;
	obstacle_source.h = 190;

	obstacle_pos.x = x;
	obstacle_pos.y = y;
	obstacle_pos.w = width;
	obstacle_pos.h = height;
}

void
Obstacle::setTextureGuardRail() {

	obstacle_source.x = 460;
	obstacle_source.y = 550;
	obstacle_source.w = 280;
	obstacle_source.h = 270;

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


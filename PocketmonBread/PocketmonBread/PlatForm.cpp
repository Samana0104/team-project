
#include "PlatForm.h"
#include <iostream>
using namespace std;


PlatForm::PlatForm(int createPos,double speed, int type)
{
	velocity = 200 * speed;;
	if (type == 0) {
		type0(createPos);
	}
	else if (type == 1) {
		type1(createPos);
	}
	
}

void
PlatForm::type0(int createPos) {
	x = 200 * createPos;
	y = 800;
	width = 200;	//speed
	height = 10;
	setTexturePlatform();
}

void
PlatForm::type1(int createPos) {
	x = 200 * createPos;
	y = 400;
	width = 200;	//speed
	height = 10;
	setTexturePlatform();
}


void
PlatForm::Update(double timestep_s)
{
	double dt = timestep_s;
	x += lround(-velocity * dt);
	
}

void
PlatForm::setTexturePlatform() {

	platform_source.x = 17;
	platform_source.y = 16;
	platform_source.w = 15;
	platform_source.h = 15;

	platform_pos.x = x;
	platform_pos.y = y;
	platform_pos.w = width;
	platform_pos.h = 200;
}

void
PlatForm::renderPlatform(SDL_Renderer* gameRenderer, SDL_Texture* platform_sheet_texture) {
	platform_pos.x = x;
	platform_pos.y = y;
	platform_pos.w = width;
	platform_pos.h = 200;

	SDL_RenderCopy(gameRenderer, platform_sheet_texture, &platform_source, &platform_pos);
}






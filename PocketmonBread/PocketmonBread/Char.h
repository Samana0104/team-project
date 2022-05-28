#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <atlstr.h>
#include "SDL.h"
#include "PlatForm.h"
#include "Obstacle.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
using namespace std;

class Char
{
public:
	//초당 좌표 200
	Char(int speed);
	void createCharTexture(SDL_Renderer* gameRenderer, string characterSheet);
	void createHeartTexture(SDL_Renderer* gameRenderer, string heartSheet);
	void createSound(string jumpwav, string damagedwav);

	void Update(double timestep_s);

	void KeyDown(SDL_Event event);
	void KeyUp(SDL_Event event);

	void charRender(SDL_Renderer* gameRenderer);
	void heartRender(SDL_Renderer* gameRenderer, int maxHeart);

	void reset(int heart);

	void setCollision_platform(PlatForm* collision) { pfCollision = collision; }
	void setCollision_obstacle(bool collision) { obCollision = collision; }
	PlatForm* Collision_PF(vector<PlatForm*> vect);
	bool Collision_OB(vector<Obstacle*> vect);

	void setSpeed(int speed) { this->speed = speed; }
	void setHeart(int heart) { this->heart = heart; }

	int getx() { return (int)x; }
	int gety() { return (int)y; }
	int getw() { return (int)width; }
	int geth() { return (int)height; }

	bool getub() { return unbeatable; }
	bool getheart() { return heart; }

protected:
	//char
	SDL_Texture* char_sheet_texture;
	SDL_Rect char_default_rect;
	SDL_Rect char_Run_rect[3];
	SDL_Rect char_jump_rect;
	SDL_Rect char_down_rect;
	SDL_Rect char_slide_rect;
	SDL_Rect char_pos;

	SDL_Texture* heart_sheet_texture;
	SDL_Rect heart_rect;

	Mix_Chunk* jumpSound;
	Mix_Chunk* damagedSound;

	double x = 200;
	double y = 200;
	int width = 100;
	int height = 200;

	//점프 가속도
	double jumpAccel = -600;

	//중력 가속도
	double gravity = 450;

	//속도
	double velocity = 0;
	
	int speed = 1;

	//입력 0이면 무입력, 1이면 슬라이딩, 2이면 점프
	int input = 0;

	// 무적여부
	bool unbeatable = false;

	// 상태 0이면 지상, 1이면 공중
	int state = 0;

	// 체력
	int heart = 3;

	//충돌여부
	bool obCollision = false;
	PlatForm* pfCollision = NULL;

	int time = 0;
	int timeset = 0;
	int unbeatalbe_time = 2000;
	int image_mod;

	void Damaged();
	void State();
	void Variance(double dt);
};


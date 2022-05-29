#include "Char.h"

//init
Char::Char(int speed) {
	this->speed = speed;
};

void
Char::createCharTexture(SDL_Renderer* gameRenderer,string characterSheet) {
	SDL_Surface* char_sheet_surface = IMG_Load(("../../resources/images/" + characterSheet).c_str());
	SDL_SetColorKey(char_sheet_surface, SDL_TRUE, SDL_MapRGB(char_sheet_surface->format, 255, 255, 255));
	char_sheet_texture = SDL_CreateTextureFromSurface(gameRenderer, char_sheet_surface);
	SDL_FreeSurface(char_sheet_surface);

	char_default_rect.x = 0;
	char_default_rect.y = 0;
	char_default_rect.w = 73;
	char_default_rect.h = 109;

	char_Run_rect[0] = { 553,435,294,438 };
	char_Run_rect[1] = { 230,124,64,96 };
	char_Run_rect[2] = { 492,124,64,96 };

	char_slide_rect.x = 517;
	char_slide_rect.y = 391;
	char_slide_rect.w = 73;
	char_slide_rect.h = 60;

	char_jump_rect.x = 860;
	char_jump_rect.y = 362;
	char_jump_rect.w = 305;
	char_jump_rect.h = 444;

	char_down_rect.x = 1207;
	char_down_rect.y = 362;
	char_down_rect.w = 266;
	char_down_rect.h = 449;

	char_pos.x = 500;
	char_pos.y = 300;
	char_pos.w = width;
	char_pos.h = height;
}

void
Char::createHeartTexture(SDL_Renderer* gameRenderer, string heartSheet) {
	SDL_Surface* heart_sheet_surface = IMG_Load(("../../resources/images/" + heartSheet).c_str());
	heart_sheet_texture = SDL_CreateTextureFromSurface(gameRenderer, heart_sheet_surface);
	SDL_FreeSurface(heart_sheet_surface);

	heart_rect.x = 0;
	heart_rect.y = 0;
	heart_rect.w = 50;
	heart_rect.h = 50;
}

void
Char::createSound(string jumpwav, string damagedwav) {
	jumpSound = Mix_LoadWAV(("../../resources/sounds/" + jumpwav).c_str());
	if (jumpSound == NULL)
	{
		printf("Couldn't load the wav: %s\n", Mix_GetError());
	}
	Mix_Volume(3, 32);
	damagedSound = Mix_LoadWAV(("../../resources/sounds/" + damagedwav).c_str());
	if (damagedSound == NULL)
	{
		printf("Couldn't load the wav: %s\n", Mix_GetError());
	}
	Mix_Volume(2, 32);
}


//Update
void
Char::Update(double timestep_s)
{
	double dt = timestep_s;
	time += (int)(dt * 1000);
	State();
	Variance(dt);
	Damaged();
}

void
Char::State() {
	// 현재 상태 공중 or 지상
	if (pfCollision && velocity >= 0) {
		state = 0;
	}
	else if (pfCollision == NULL) {
		state = 1;
	}
}

void
Char::Variance(double dt) {
	if (state == 0 && input == 0 && pfCollision) {
		y = pfCollision->gety() - 199;
		height = 200;
		velocity = 0;
	}
	else if (state == 0 && input == 1 && pfCollision) {
		y = pfCollision->gety() - 99;
		height = 100;
		velocity = 0;
	}
	else if (state == 1) {
		height = 200;
		y += velocity * dt;
		velocity += gravity * dt * speed*speed;
	}
}

void
Char::Damaged() {
	if (obCollision && !unbeatable) {
		heart -= 1;
		unbeatable = true;
		timeset = time;
		Mix_Volume(2,64);
		Mix_PlayChannel(2, damagedSound, 0);
		cout << "체력 감소 : " << heart << "\n";
	}
	else if ((y > 900)) {
		y = 201;
		if (!unbeatable) {
			heart -= 1;
			unbeatable = true;
			timeset = time;
			Mix_Volume(2,64);
			cout << "체력 감소 : " << heart << "\n";
		}
	}
	if (time - timeset > unbeatalbe_time) {
		unbeatable = false;
	}
}

//handle
void
Char::KeyDown(SDL_Event event) {
	if (event.key.keysym.sym == SDLK_SPACE && (state == 0) && pfCollision) {
		y = pfCollision->gety() - 200;
		pfCollision = NULL;
		height = 200;
		velocity += jumpAccel * speed;
		Mix_Volume(3,64);
		Mix_PlayChannel(3, jumpSound, 0);

	}
	else if (event.key.keysym.sym == SDLK_DOWN && (state == 0)) {
		input = 1;
	}
}

void
Char::KeyUp(SDL_Event event) {
	if (event.key.keysym.sym == SDLK_DOWN) {
		input = 0;
	}
}

//render
void
Char::charRender(SDL_Renderer* gameRenderer) {
	
	char_pos.x = x;
	char_pos.y = y;
	char_pos.w = width;
	char_pos.h = height;

	if (unbeatable) {
		if (time - timeset < 100) {
			SDL_SetTextureColorMod(char_sheet_texture, 255, 0, 0);
		}
		else {
			SDL_SetTextureColorMod(char_sheet_texture, 255, 255, 255);
		}
		SDL_SetTextureAlphaMod(char_sheet_texture, 100);
	}
	else {
		SDL_SetTextureColorMod(char_sheet_texture, 255, 255, 255);
		SDL_SetTextureAlphaMod(char_sheet_texture, 255);
	}
	
	if (state == 0 && input == 0) {
		SDL_Rect temp;
		if (time % (1500 / speed) >= 0 && time % (1500 / speed) <= 500 / speed) {
			temp = char_Run_rect[0];
		}
		if (time % (1500 / speed) > 500 / speed && time % (1500 / speed) <= 1000 / speed) {
			temp = char_Run_rect[1];
		}
		if (time % (1500 / speed) > 1000 / speed && time % (1500 / speed) <= 1500 / speed) {
			temp = char_Run_rect[2];
		}
		SDL_RenderCopyEx(gameRenderer, char_sheet_texture, &temp, &char_pos, 0, 0, SDL_FLIP_HORIZONTAL);
	}
	else if (state == 0 && input == 1) {
		SDL_RenderCopyEx(gameRenderer, char_sheet_texture, &char_slide_rect, &char_pos, 0, 0, SDL_FLIP_HORIZONTAL);
	}
	else if (state == 1 && velocity > 0) {
		SDL_RenderCopyEx(gameRenderer, char_sheet_texture, &char_jump_rect, &char_pos, 0, 0, SDL_FLIP_HORIZONTAL);
	}
	else if (state == 1 && velocity <= 0) {
		SDL_RenderCopyEx(gameRenderer, char_sheet_texture, &char_down_rect, &char_pos, 0, 0, SDL_FLIP_HORIZONTAL);
	}
	
}

void
Char::heartRender(SDL_Renderer* gameRenderer,int maxHeart) {
	for (int i = 0; i < maxHeart; i++){
		SDL_Rect temp;
		temp.x = 0 + 50 * i;
		temp.y = 0;
		temp.w = 50;
		temp.h = 50;
		if (i >= heart) 
			SDL_SetTextureColorMod(heart_sheet_texture, 0, 0, 0);
		else 
			SDL_SetTextureColorMod(heart_sheet_texture, 255, 255, 255);
		SDL_RenderCopy(gameRenderer, heart_sheet_texture, &heart_rect, &temp);
	}
		
}

//char 초기화
void
Char::reset(int heart) {
	this->heart = heart;
	unbeatable = false;
	state = 0;
	input = 0;
	y = 200;
	height = 200;
	velocity = 0;
}

//지상 충돌
PlatForm*
Char::Collision_PF(vector<PlatForm*> vect)
{
	int A_Left = x;
	int A_Top = y + height / 1.5;
	int A_Right = x +width;;
	int A_Bottom = y + height;

	if (!vect.empty()) {
		for (int i = 0; i < vect.size(); i++) {
			int B_Left = vect.at(i)->getx();
			int B_Top = vect.at(i)->gety();
			int B_Right = vect.at(i)->getx() + vect.at(i)->getw();
			int B_Bottom = vect.at(i)->gety() + vect.at(i)->geth()/5;
			if ((A_Bottom > B_Top) && (A_Top < B_Bottom) && (A_Right > B_Left) && (A_Left < B_Right)) {
				return vect.at(i);
			}
		}
	}
	return NULL;
}

//장애물 충돌
bool
Char::Collision_OB(vector<Obstacle*> vect)
{
	int A_Left = x;
	int A_Top = y;
	int A_Right = x + width;;
	int A_Bottom = y + height;

	if (!vect.empty()) {
		for (int i = 0; i < vect.size(); i++) {
			int B_Left = vect.at(i)->getx();
			int B_Top = vect.at(i)->gety();
			int B_Right = vect.at(i)->getx() + vect.at(i)->getw();
			int B_Bottom = vect.at(i)->gety() + vect.at(i)->geth();
			if ((A_Bottom > B_Top) && (A_Top < B_Bottom) && (A_Right > B_Left) && (A_Left < B_Right)) {
				return true;
			}
		}
	}
	return false;
}






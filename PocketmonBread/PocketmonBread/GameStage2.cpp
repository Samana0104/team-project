#include "GameStage2.h"



Stage2::Stage2(SDL_Window* gameWindow, SDL_Renderer* gameRenderer) : PhaseInterface(gameWindow, gameRenderer)
{
	this->buttonEffectSound = Mix_LoadWAV("../../resources/sounds/intro_button_sound.mp3");
	createBackGroundTexture(gameRenderer, "stage_background.png");
	createObstacleTexture(gameRenderer, "Tileset.png");
	createPlatformTexture(gameRenderer, "Tileset.png");	
	createMusic("Stage_bgm01.mp3");
	createClearMusic("stage_clear_bgm.mp3");
	createCounterSound("stage_sfx_countdown.wav", "stage_sfx_start.wav");
	createFont(gameRenderer, "DungGeunMo.ttf");

	createBackButton(gameRenderer);
	createRetryButton(gameRenderer);
	createMouseCursor();

	CH->createCharTexture(getGameRenderer(), "stage2_goal.png");	
	CH->createSound("stage_sfx_jump.wav", "stage_sfx_slide.wav");		
	CH->createHeartTexture(getGameRenderer(), "heart_full.png");
}

Stage2::~Stage2()
{
	delete point;
	delete CH;
}

void Stage2::updateDatas()
{
	if (gameSituation() == 1) {
		gameStand();
	}
	else if (gameSituation() == 2) {
		gameOver();
	}
	else if (gameSituation() == 3) {
		gameClear();
	}
	else {
		gamePlay();
	}
	gameSituation();

	g_elapsed_time_ms += lround(0.01 * (float)1000);
}

void Stage2::renderFrames()
{
	SDL_RenderClear(getGameRenderer()); // clear the renderer to the draw color
	renderBackGround();

	//platform
	if (!PF.empty()) {
		for (int i = 0; i < PF.size(); i++) {
			PF.at(i)->renderPlatform(getGameRenderer(), platform_sheet_texture);
		}
	}

	//OB
	if (!OB.empty()) {
		for (int i = 0; i < OB.size(); i++) {
			OB.at(i)->renderObstacle(getGameRenderer(), Obstacle_sheet_texture);
		}
	}
	//Char
	CH->charRender(getGameRenderer());
	CH->heartRender(getGameRenderer(), HEART);

	renderCounter();
	if (gameSituation() == 2) {
		renderButtons();
	}

	SDL_SetRenderDrawColor(getGameRenderer(), 0, 0, 255, 0);
	SDL_RenderPresent(getGameRenderer()); // draw to the screen
}

void Stage2::handleEvents(const SDL_Event& gameEvent)
{

	this->presentMousePos.x = gameEvent.button.x;
	this->presentMousePos.y = gameEvent.button.y;

	switch (gameEvent.type)
	{
	case SDL_KEYDOWN:
		if (gameSituation() == 0) {
			CH->KeyDown(gameEvent);
		}
		break;

	case SDL_KEYUP:
		if (gameSituation() == 0) {
			CH->KeyUp(gameEvent);
		}
		break;

	case SDL_MOUSEBUTTONDOWN:

		// If the mouse left button is pressed. 
		if (gameEvent.button.button == SDL_BUTTON_LEFT && gameSituation() == 2)
		{
			clickButtonsInRange(gameEvent.button.x, gameEvent.button.y);
		}
		else if (gameEvent.button.button == SDL_BUTTON_LEFT && gameSituation() == 3){
			setNextGamePhase(GAME_PHASE::MAIN);
		}
		break;

	default:
		break;
		
	}
	
}

void Stage2::openPhase() {
	this->presentMousePos.x = 0;
	this->presentMousePos.y = 0;
	CH->setSpeed(SPEED);

	for (int i = 0; i < DISTANCE + 8; i++) {
		point[i] = { "001" };
	}

	Mix_VolumeMusic(24);
	Mix_Volume(1, 32);
	reset();
	setNextGamePhase(GAME_PHASE::NONE);
}

void Stage2::closePhase() {
	SDL_SetCursor(this->mouseArrowCursor);
	Mix_HaltMusic();
}

// init
void
Stage2::createBackGroundTexture(SDL_Renderer* gameRenderer, string BG) {
	SDL_Surface* bg_sheet_surface = IMG_Load(("../../resources/images/" + BG).c_str());
	bg_sheet_texture = SDL_CreateTextureFromSurface(gameRenderer, bg_sheet_surface);
	SDL_FreeSurface(bg_sheet_surface);

	bg_source_rect.x = 0;
	bg_source_rect.y = 0;
	bg_source_rect.w = 1280;
	bg_source_rect.h = 720;

	bg_destination_rect.x = 0;
	bg_destination_rect.y = 0;
	bg_destination_rect.w = 10000;
	bg_destination_rect.h = 900;
}

void
Stage2::createObstacleTexture(SDL_Renderer* gameRenderer,string obstacleSheet) {
	SDL_Surface* Obstacle_sheet_surface = IMG_Load(("../../resources/images/" + obstacleSheet).c_str());
	Obstacle_sheet_texture = SDL_CreateTextureFromSurface(gameRenderer, Obstacle_sheet_surface);
	SDL_FreeSurface(Obstacle_sheet_surface);
}

void
Stage2::createPlatformTexture(SDL_Renderer* gameRenderer,string platformSheet) {
	SDL_Surface* platform_sheet_surface = IMG_Load(("../../resources/images/" + platformSheet).c_str());
	platform_sheet_texture = SDL_CreateTextureFromSurface(gameRenderer, platform_sheet_surface);
	SDL_FreeSurface(platform_sheet_surface);
}

void
Stage2::createMusic(string BGM) {
	bgm = Mix_LoadMUS(("../../resources/sounds/" + BGM).c_str());
	if (!bgm)
	{
		printf(" %s\n", Mix_GetError());
		// this might be a critical error...
	}
}

void
Stage2::createClearMusic(string ClearBGM) {
	clearbgm = Mix_LoadMUS(("../../resources/sounds/" + ClearBGM).c_str());
	if (!clearbgm)
	{
		printf(" %s\n", Mix_GetError());
		// this might be a critical error...
	}
}

void
Stage2::createCounterSound(string counter,string start) {
	const char* file = ("../../resources/sounds/"+counter).c_str();
	counterSound = Mix_LoadWAV(file);
	if (counterSound == NULL)
	{
		printf("Couldn't load the wav: %s\n", Mix_GetError());
	}
	start = "../../resources/sounds/" + start;
	file = start.c_str();
	startSound = Mix_LoadWAV(file);
	if (startSound == NULL)
	{
		printf("Couldn't load the wav: %s\n", Mix_GetError());
	}
	Mix_Volume(1, 32);
}

void
Stage2::createFont(SDL_Renderer* gameRenderer,string font) {
	font1 = TTF_OpenFont(("../../resources/fonts/" + font).c_str(), 50);
	temp = TTF_RenderText_Blended(font1, " ", { 255,0,0,0 });

	counter_rect.x = 0;
	counter_rect.y = 0;
	counter_rect.w = 50;
	counter_rect.h = 50;

	counter_sheet_texture = SDL_CreateTextureFromSurface(gameRenderer, temp);
	SDL_FreeSurface(temp);
}


void
Stage2::createRetryButton(SDL_Renderer* gameRenderer)
{
	SDL_Rect texturePos = { 0, 0, 489, 121 };
	SDL_Rect renderingPos = { 607, 600, 387, 84 };

	SDL_Surface* tmpSurface = IMG_Load("../../resources/images/stage_agin_button.png");
	this->stageButtons[STAGE2_BUTTON::RETRY_BUTTON] = new RectangleButton(texturePos, renderingPos, SDL_CreateTextureFromSurface(gameRenderer, tmpSurface));
	SDL_FreeSurface(tmpSurface);
}

void
Stage2::createBackButton(SDL_Renderer* gameRenderer)
{
	SDL_Rect texturePos = { 0, 0, 489, 121 };
	SDL_Rect renderingPos = { 607, 700, 387, 84 };

	SDL_Surface* tmpSurface = IMG_Load("../../resources/images/stage_exit_button.png");
	this->stageButtons[STAGE2_BUTTON::BACK_BUTTON] = new RectangleButton(texturePos, renderingPos, SDL_CreateTextureFromSurface(gameRenderer, tmpSurface));
	SDL_FreeSurface(tmpSurface);
}

void 
Stage2::createMouseCursor()
{
	this->mouseArrowCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
	this->mouseHandCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
}

void 
Stage2::clickButtonsInRange(const int& mouseXPos, const int& mouseYPos)
{
	for (int i = 0; i < STAGE2_BUTTON::COUNT; i++)
	{
		if (this->stageButtons[i]->isClickingButtonInRange(mouseXPos, mouseYPos))
			selectButtonType(static_cast<STAGE2_BUTTON::TYPE>(i));
	}
	Mix_PlayChannel(1, this->buttonEffectSound, 0);
}

void
Stage2::selectButtonType(const STAGE2_BUTTON::TYPE& buttonType)
{

	switch (buttonType)
	{
	case STAGE2_BUTTON::BACK_BUTTON:
		setNextGamePhase(GAME_PHASE::MAIN);
		break;
	case STAGE2_BUTTON::RETRY_BUTTON:
		reset();
		break;
	}

}

void
Stage2::renderButtons()
{
	bool isMouseInRange = false;
	for (int i = 0; i < STAGE2_BUTTON::COUNT; i++)
	{
		if (this->stageButtons[i]->isClickingButtonInRange(this->presentMousePos.x, this->presentMousePos.y))
		{
			SDL_SetCursor(this->mouseHandCursor);
			this->stageButtons[i]->RenderButtonTextureOnButton(getGameRenderer());
			isMouseInRange = true;
		}
		else
		{
			this->stageButtons[i]->RenderButtonTexture(getGameRenderer());
		}
	}

	if (!isMouseInRange) // 이게 없으면 버튼이 범위안에 있어도 커서가 화살표로 바뀜
		SDL_SetCursor(this->mouseArrowCursor);
}


void
Stage2::levelDesign() {
	// 생성 규칙
	// 1의 자리는 층 여부
	// xx0	없음 
	// xx1	1층
	// xx2	2층
	// xx3	1,2층
	// 10의 자리는 2층 장애물 여부
	// x0x  장애물 없음
	// x1x	가드레일
	// x2x	새떼
	// x3x  둘다
	// 1의 자리는 1층 장애물 여부
	// 0xx  장애물 없음
	// 1xx	가드레일
	// 2xx	새떼
	// 3xx  둘다
	//

	//stage2장애물 설정
	//DISTANCE 158
	//SPEED 3
	point[1 + 8] = "000";
	point[2 + 8] = "000"; 
	point[7 + 8] = "000";
	point[8 + 8] = "000";
	point[11 + 8] = "101";
	point[16 + 8] = "201";
	point[17 + 8] = "201";
	point[18 + 8] = "201";
	point[19 + 8] = "201";
	point[24 + 8] = "101";
	point[29 + 8] = "000";
	point[30 + 8] = "000";
	point[32 + 8] = "101";
	point[37 + 8] = "000";
	point[38 + 8] = "000";
	point[41 + 8] = "201";
	point[42 + 8] = "201";
	point[43 + 8] = "201";
	point[44 + 8] = "201";

	point[50 + 8] = "003";
	point[51 + 8] = "003";
	point[52 + 8] = "003";
	point[53 + 8] = "003";
	point[54 + 8] = "103";
	point[55 + 8] = "103";
	point[56 + 8] = "213";
	point[57 + 8] = "203";
	point[58 + 8] = "003";
	point[59 + 8] = "003";

	point[65 + 8] = "000";
	point[66 + 8] = "000";
	point[71 + 8] = "000";
	point[72 + 8] = "000";
	point[75 + 8] = "003";
	point[76 + 8] = "103";
	point[77 + 8] = "203";
	point[78 + 8] = "103";
	point[79 + 8] = "103";
	point[80 + 8] = "002";
	point[81 + 8] = "002";
	point[82 + 8] = "003";
	point[83 + 8] = "003";
	point[84 + 8] = "022";
	point[85 + 8] = "022";
	point[86 + 8] = "002";
	point[87 + 8] = "000";
	point[88 + 8] = "000";
	point[89 + 8] = "002";
	point[90 + 8] = "002";
	point[91 + 8] = "002";

	point[98 + 8] = "201";
	point[101 + 8] = "021";
	point[103 + 8] = "201";

	point[109 + 8] = "003";
	point[110 + 8] = "003";
	point[111 + 8] = "203";
	point[112 + 8] = "203";
	point[113 + 8] = "203";
	point[114 + 8] = "013";
	point[115 + 8] = "003";
	point[116 + 8] = "003";
	point[117 + 8] = "013";
	point[118 + 8] = "003";
	point[119 + 8] = "003";
	point[120 + 8] = "023";
	point[121 + 8] = "023";
	point[122 + 8] = "023";

	point[130 + 8] = "000";
	point[131 + 8] = "000";
	point[132 + 8] = "002";
	point[133 + 8] = "002";
	point[134 + 8] = "002";
	point[135 + 8] = "002";
	point[136 + 8] = "000";
	point[137 + 8] = "000";
	point[138 + 8] = "000";
	
}

//
//
//render
void
Stage2::renderBackGround() {
	SDL_RenderCopy(getGameRenderer(), bg_sheet_texture, &bg_source_rect, &bg_destination_rect);
}

//gamesituation 사용
void
Stage2::renderCounter() {
	if (gameSituation() == 1) {
		SDL_Rect temp;
		temp.x = 700;
		temp.y = 400;
		temp.w = 200;
		temp.h = 50;
		SDL_RenderCopy(getGameRenderer(), counter_sheet_texture, &counter_rect, &temp);
	}
	else if (gameSituation() == 3) {
		SDL_Rect temp;
		temp.x = 700;
		temp.y = 400;
		temp.w = 200;
		temp.h = 50;
		SDL_RenderCopy(getGameRenderer(), title_sheet_texture, &title_rect, &temp);
	}
	else if (gameSituation() == 2) {
		SDL_Rect temp;
		temp.x = 700;
		temp.y = 400;
		temp.w = 200;
		temp.h = 50;
		SDL_RenderCopy(getGameRenderer(), title_sheet_texture, &title_rect, &temp);
	}

}

//

// 
// 
//UPdate
int
Stage2::gameSituation() {
	//시작 대기
	if (g_elapsed_time_ms - startTimer < 4000) {
		return 1;
	}
	//게임 오버
	else if(CH->getheart() == 0) {
		return 2;
	}
	//게임 클리어
	else if (time == PLAYTIME) {
		return 3;
	}
	//게임 플레이
	else {
		return 0;
	}

}

//
//fieldUpdate
//Collision
//사용
void
Stage2::gamePlay() {
	if (g_elapsed_time_ms - start >= 1000) {
		start = g_elapsed_time_ms;
		time += 1;
		cout << time;
	}
	bg_destination_rect.x -= 1 * SPEED;
	if (!PF.empty()) {
		for (int i = 0; i < PF.size(); i++) {
			PF.at(i)->Update(0.01);
			if (PF.at(i)->getx() <= -500) {
				delete PF[i];
				PF.erase(PF.begin() + i);
			}
		}
	}
	if (!OB.empty()) {
		for (int i = 0; i < OB.size(); i++) {
			OB.at(i)->Update(0.01);
			if (OB.at(i)->getx() <= -500) {
				delete OB[i];
				OB.erase(OB.begin() + i);
			}
		}
	}

	if (time == PLAYTIME) {
		Mix_HaltMusic();
	}

	CH->setCollision_platform(CH->Collision_PF(PF));
	CH->setCollision_obstacle(CH->Collision_OB(OB));
	CH->Update(0.01);
}

void
Stage2::gameStand() {
	SDL_DestroyTexture(counter_sheet_texture);
	if (g_elapsed_time_ms - startTimer >= 0 && g_elapsed_time_ms - startTimer < 1000) {
		if(g_elapsed_time_ms - startTimer == 0 )
			Mix_PlayChannel(1, counterSound, 0);
		temp = TTF_RenderText_Blended(font1, "  3  ", { 255,0,0,0 });
	}
	else if (g_elapsed_time_ms - startTimer >= 1000 && g_elapsed_time_ms - startTimer < 2000) {
		if (g_elapsed_time_ms - startTimer == 1000 )
			Mix_PlayChannel(1, counterSound, 0);
		temp = TTF_RenderText_Blended(font1, "  2  ", { 255,0,0,0 });
	}
	else if (g_elapsed_time_ms - startTimer >= 2000 && g_elapsed_time_ms - startTimer < 3000) {
		if (g_elapsed_time_ms - startTimer == 2000)
			Mix_PlayChannel(1, counterSound, 0);
		temp = TTF_RenderText_Blended(font1, "  1  ", { 255,0,0,0 });
	}
	else {
		if (g_elapsed_time_ms - startTimer == 3000)
			Mix_PlayChannel(1, startSound, 0);
		temp = TTF_RenderText_Blended(font1, "START!!", { 255,0,0,0 });
	}
	counter_rect.x = 0;
	counter_rect.y = 0;
	counter_rect.w = temp->w;
	counter_rect.h = temp->h;

	counter_sheet_texture = SDL_CreateTextureFromSurface(getGameRenderer(), temp);
	SDL_FreeSurface(temp);
}

void
Stage2::gameOver() {
	Mix_FadeOutMusic(2000);
	SDL_DestroyTexture(title_sheet_texture);
	temp = TTF_RenderText_Blended(font1, "GAME OVER", { 255,0,0,0 });
	title_rect.x = 0;
	title_rect.y = 0;
	title_rect.w = temp->w;
	title_rect.h = temp->h;

	title_sheet_texture = SDL_CreateTextureFromSurface(getGameRenderer(), temp);
	SDL_FreeSurface(temp);
	//재시작 버튼과 타이틀로 돌아가기 버튼
}

void
Stage2::gameClear() {
	if (Mix_PlayingMusic() == 0) {
		Mix_VolumeMusic(64);
		Mix_PlayMusic(clearbgm, -1);
	}
	SDL_DestroyTexture(title_sheet_texture);
	temp = TTF_RenderText_Blended(font1, "STAGE CLEAR", { 255,0,0,0 });
	title_rect.x = 0;
	title_rect.y = 0;
	title_rect.w = temp->w;
	title_rect.h = temp->h;

	title_sheet_texture = SDL_CreateTextureFromSurface(getGameRenderer(), temp);
	SDL_FreeSurface(temp);
	//타이틀로 돌아가기 버튼
}

void
Stage2::fieldLoad() {
	for (int location = 8; location < DISTANCE; location++) {
		if (point[location][2] == 49) {
			//1층 가드레일
			PF.push_back(new PlatForm(location,SPEED, 0));
		}
		else if (point[location][2] == 50) {
			//1층 새떼
			PF.push_back(new PlatForm(location, SPEED, 1));
		}
		else if (point[location][2] == 51) {
			//1층 모두
			PF.push_back(new PlatForm(location, SPEED, 0));
			PF.push_back(new PlatForm(location, SPEED, 1));
		}

		if (point[location][1] == 49) {
			//2층 가드레일
			OB.push_back(new Obstacle(location, SPEED, 2));
		}
		else if (point[location][1] == 50) {
			//2층 새떼
			OB.push_back(new Obstacle(location, SPEED, 3));
		}
		else if (point[location][1] == 51) {
			//2층 가드레일 새떼
			OB.push_back(new Obstacle(location, SPEED, 2));
			OB.push_back(new Obstacle(location, SPEED, 3));
		}

		if (point[location][0] == 49) {
			//1층
			OB.push_back(new Obstacle(location, SPEED, 0));
		}
		else if (point[location][0] == 50) {
			//2층
			OB.push_back(new Obstacle(location, SPEED, 1));
		}
		else if (point[location][0] == 51) {
			//모두
			OB.push_back(new Obstacle(location, SPEED, 0));
			OB.push_back(new Obstacle(location, SPEED, 1));
		}
	}
}

//현재 페이즈 초기화
void
Stage2::reset() {
	Mix_FadeOutMusic(0);
	if (!OB.empty()) {
		OB.clear();
	}

	if (!PF.empty()) {
		PF.clear();
	}

	PF.push_back(new PlatForm(0, SPEED, 0));
	PF.push_back(new PlatForm(1, SPEED, 0));
	PF.push_back(new PlatForm(2, SPEED, 0));
	PF.push_back(new PlatForm(3, SPEED, 0));
	PF.push_back(new PlatForm(4, SPEED, 0));
	PF.push_back(new PlatForm(5, SPEED, 0));
	PF.push_back(new PlatForm(6, SPEED, 0));
	PF.push_back(new PlatForm(7, SPEED, 0));

	bg_destination_rect.x = 0;

	startTimer = g_elapsed_time_ms;
	start = 0;
	time = 0;
	Mix_VolumeMusic(24);
	Mix_PlayMusic(bgm, -1);
	CH->reset(HEART);
	levelDesign();
	fieldLoad();
}




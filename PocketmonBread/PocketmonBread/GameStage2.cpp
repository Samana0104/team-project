#include "GameStage2.h"



Stage2::Stage2(SDL_Window* gameWindow, SDL_Renderer* gameRenderer) : PhaseInterface(gameWindow, gameRenderer)
{
createBackGroundTexture(gameRenderer, "ddd.jpg");
createObstacleTexture(gameRenderer, "sheet.png");
createPlatformTexture(gameRenderer, "Tileset.png");	
createMusic("Kalimba.mp3");
createClearMusic("music.mp3");
createCounterSound("pluck-pcm8.wav", "DM-CGS-43.wav");
createFont(gameRenderer, "Chlorinp.ttf");

createStartButton(gameRenderer);
createRetryButton(gameRenderer);
createMouseCursor();

CH->createCharTexture(getGameRenderer(), "60224.png");	
CH->createSound("ARROW.wav", "WHOOSH.wav");		
CH->createHeartTexture(getGameRenderer(), "Heart.png");
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

	Mix_VolumeMusic(32);
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
	SDL_Surface* bg_sheet_surface = IMG_Load(("../../resources/test/" + BG).c_str());
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
	SDL_Surface* Obstacle_sheet_surface = IMG_Load(("../../resources/test/" + obstacleSheet).c_str());
	Obstacle_sheet_texture = SDL_CreateTextureFromSurface(gameRenderer, Obstacle_sheet_surface);
	SDL_FreeSurface(Obstacle_sheet_surface);
}

void
Stage2::createPlatformTexture(SDL_Renderer* gameRenderer,string platformSheet) {
	SDL_Surface* platform_sheet_surface = IMG_Load(("../../resources/test/" + platformSheet).c_str());
	platform_sheet_texture = SDL_CreateTextureFromSurface(gameRenderer, platform_sheet_surface);
	SDL_FreeSurface(platform_sheet_surface);
}

void
Stage2::createMusic(string BGM) {
	bgm = Mix_LoadMUS(("../../resources/test/" + BGM).c_str());
	if (!bgm)
	{
		printf(" %s\n", Mix_GetError());
		// this might be a critical error...
	}
}

void
Stage2::createClearMusic(string ClearBGM) {
	clearbgm = Mix_LoadMUS(("../../resources/test/" + ClearBGM).c_str());
	if (!clearbgm)
	{
		printf(" %s\n", Mix_GetError());
		// this might be a critical error...
	}
}

void
Stage2::createCounterSound(string counter,string start) {
	const char* file = ("../../resources/test/"+counter).c_str();
	counterSound = Mix_LoadWAV(file);
	if (counterSound == NULL)
	{
		printf("Couldn't load the wav: %s\n", Mix_GetError());
	}
	start = "../../resources/test/" + start;
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
	font1 = TTF_OpenFont(("../../resources/test/" + font).c_str(), 50);
	temp = TTF_RenderText_Blended(font1, " ", { 255,0,0,0 });

	counter_rect.x = 0;
	counter_rect.y = 0;
	counter_rect.w = 50;
	counter_rect.h = 50;

	counter_sheet_texture = SDL_CreateTextureFromSurface(gameRenderer, temp);
	SDL_FreeSurface(temp);
}


void
Stage2::createStartButton(SDL_Renderer* gameRenderer)
{
	SDL_Rect texturePos = { 0, 0, 387, 84 };
	SDL_Rect renderingPos = { 607, 600, 387, 84 };

	SDL_Surface* tmpSurface = IMG_Load("../../resources/test/images/intro_start_button.png");
	this->stageButtons[STAGE_BUTTON2::RETRY_BUTTON] = new RectangleButton(texturePos, renderingPos, SDL_CreateTextureFromSurface(gameRenderer, tmpSurface));
	SDL_FreeSurface(tmpSurface);
}

void
Stage2::createRetryButton(SDL_Renderer* gameRenderer)
{
	SDL_Rect texturePos = { 0, 0, 387, 84 };
	SDL_Rect renderingPos = { 607, 700, 387, 84 };

	SDL_Surface* tmpSurface = IMG_Load("../../resources/test/images/intro_end_button.png");
	this->stageButtons[STAGE_BUTTON2::BACK_BUTTON] = new RectangleButton(texturePos, renderingPos, SDL_CreateTextureFromSurface(gameRenderer, tmpSurface));
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
	for (int i = 0; i < STAGE_BUTTON2::COUNT; i++)
	{
		if (this->stageButtons[i]->isClickingButtonInRange(mouseXPos, mouseYPos))
			selectButtonType(static_cast<STAGE_BUTTON2::TYPE>(i));
	}
}

void
Stage2::selectButtonType(const STAGE_BUTTON2::TYPE& buttonType)
{

	switch (buttonType)
	{
	case STAGE_BUTTON2::BACK_BUTTON:
		setNextGamePhase(GAME_PHASE::MAIN);
		break;
	case STAGE_BUTTON2::RETRY_BUTTON:
		reset();
		break;
	}

}

void
Stage2::renderButtons()
{
	bool isMouseInRange = false;
	for (int i = 0; i < STAGE_BUTTON2::COUNT; i++)
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



	//장애물 설정
	
	//2층 장애물
	point[4+8] = "000";
	point[8 + 8] = "010";
	point[12 + 8] = "020";
	point[16 + 8] = "030";

	//2층 장애물 1층
	point[20 + 8] = "001";
	point[24 + 8] = "011";
	point[28 + 8] = "021";
	point[32 + 8] = "031";

	//2층 장애물 2층
	point[36 + 8] = "002";
	point[40 + 8] = "012";
	point[44 + 8] = "022";
	point[48 + 8] = "032";

	//2층 장애물 1,2층
	point[52+ 8] = "003";
	point[56+ 8] = "013";
	point[60+ 8] = "023";
	point[64+ 8] = "033";

	/*
	//2층 장애물들
	point[4] = 100;
	point[8] = 110;
	point[12] = 120;
	point[16] = 130;
	//1층 가드레일 2층 장애물들
	point[20] = 101;
	point[24] = 111;
	point[28] = 121;
	point[32] = 131;
	//1층 벌떼 2층 장애물들
	point[36] = 102;
	point[40] = 112;
	point[44] = 122;
	point[48] = 132;
	//1층 모든 장애물 2층 장애물들
	point[52] = 103;
	point[56] = 113;
	point[60] = 123;
	point[64] = 133;
	*/
	/*
	point[4] = 200;
	point[8] = 210;
	point[12] = 220;
	point[16] = 230;
	point[20] = 201;
	point[24] = 211;
	point[28] = 221;
	point[32] = 231;
	point[36] = 202;
	point[40] = 212;
	point[44] = 222;
	point[48] = 232;
	point[52] = 203;
	point[56] = 213;
	point[60] = 223;
	point[64] = 233;
	*/
	/*
	point[4] = 300;
	point[8] = 310;
	point[12] = 320;
	point[16] = 330;
	point[20] = 301;
	point[24] = 311;
	point[28] = 321;
	point[32] = 331;
	point[36] = 302;
	point[40] = 312;
	point[44] = 322;
	point[48] = 332;
	point[52] = 303;
	point[56] = 313;
	point[60] = 323;
	point[64] = 333;
	*/

	


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
		temp = TTF_RenderText_Blended(font1, "start", { 255,0,0,0 });
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
	temp = TTF_RenderText_Blended(font1, "GameOver", { 255,0,0,0 });
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
		Mix_PlayMusic(clearbgm, -1);
	}
	SDL_DestroyTexture(title_sheet_texture);
	temp = TTF_RenderText_Blended(font1, "GameClear", { 255,0,0,0 });
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
	Mix_PlayMusic(bgm, -1);
	CH->reset(HEART);
	levelDesign();
	fieldLoad();
}




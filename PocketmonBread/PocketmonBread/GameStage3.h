#pragma once

#include "PhaseInterface.h"
#include "RectangleButton.h"

#include "Char.h"
#include "PlatForm.h"
#include "obstacle.h"

#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include <list>
#define DISTANCE 208
#define SPEED 4
#define HEART 5
#define PLAYTIME 50
#define BLOCK 200


using namespace std;

namespace STAGE3_BUTTON
{
	enum TYPE
	{
		BACK_BUTTON = 0,
		RETRY_BUTTON = 1,
		COUNT = 2
	};
}

class Stage3 : public PhaseInterface
{
public:
	Stage3(SDL_Window* gameWindow, SDL_Renderer* gameRender, Player* _gamePlayer);
	virtual ~Stage3();

	virtual void handleEvents(const SDL_Event&);
	virtual void updateDatas();
	virtual void renderFrames();
	virtual void openPhase();
	virtual void closePhase();

private:
	void createBackGroundTexture(SDL_Renderer* gameRenderer,string BG);
	void createObstacleTexture(SDL_Renderer* gameRenderer,string obstacleSheet);
	void createPlatformTexture(SDL_Renderer* gameRenderer,string platformSheet);
	void createMusic(string BGM);
	void createClearMusic(string ClearBGM);
	void createCounterSound(string counter, string start);
	void createFont(SDL_Renderer* gameRenderer,string font);

	void createBackButton(SDL_Renderer* gameRenderer);
	void createRetryButton(SDL_Renderer* gameRenderer);
	void createMouseCursor();
	void clickButtonsInRange(const int& mouseXPos, const int& mouseYPos);
	void selectButtonType(const STAGE3_BUTTON::TYPE& buttonType);
	void renderButtons();

	void renderBackGround();
	void renderCounter();

	void reset();
	void levelDesign();
	void fieldLoad();

	void gamePlay();
	void gameOver();
	void gameClear();
	void gameStand();

	int gameSituation();

	Player* gamePlayer;

	SDL_Rect bg_source_rect;
	SDL_Rect bg_destination_rect;
	SDL_Texture* bg_sheet_texture;
	SDL_Texture* Obstacle_sheet_texture;
	SDL_Texture* platform_sheet_texture;

	Mix_Music* bgm;
	Mix_Music* clearbgm;

	Mix_Chunk* counterSound;
	Mix_Chunk* startSound;

	SDL_Texture* counter_sheet_texture;
	SDL_Texture* title_sheet_texture;
	SDL_Rect counter_rect;
	SDL_Rect title_rect;
	TTF_Font* font1;
	SDL_Surface* temp;

	vector <PlatForm*> PF;
	vector <Obstacle*> OB;
	Char *CH = new Char(SPEED);

	RectangleButton* stageButtons[STAGE3_BUTTON::COUNT];
	SDL_Cursor* mouseArrowCursor;
	SDL_Cursor* mouseHandCursor;
	SDL_Rect presentMousePos;
	Mix_Chunk* buttonEffectSound;

	// 시간
	int time;

	string point[DISTANCE+8];

	// 시작 타이머
	double startTimer;
	// 초 세기용
	double start;
	// 본 게임을 한 시간
	double g_elapsed_time_ms;
};
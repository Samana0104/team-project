#include "MainHandler.h"
#include "ConstantDecl.h"

int main(int argc, char* argv[])
{
	MainHandler gameManager(GAME_WINDOW::WIDTH, GAME_WINDOW::HEIGHT); // 게임창 가로크기 , 게임창 세로크기
	gameManager.gameStart();
	return 0;
}


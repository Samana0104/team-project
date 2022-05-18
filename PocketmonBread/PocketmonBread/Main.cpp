#include "MainHandler.h"

int main(int argc, char* argv[])
{
	MainHandler gameManager(1600, 900); // 게임창 가로크기 , 게임창 세로크기
	gameManager.gameStart();
	return 0;
}


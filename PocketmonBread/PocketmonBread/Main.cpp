#include "MainHandler.h"
#include "ConstantDecl.h"

int main(int argc, char* argv[])
{
	MainHandler gameManager(GAME_WINDOW::WIDTH, GAME_WINDOW::HEIGHT); // ����â ����ũ�� , ����â ����ũ��
	gameManager.gameStart();
	return 0;
}


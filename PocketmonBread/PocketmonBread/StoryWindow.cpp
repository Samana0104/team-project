#include "StoryWindow.h"
#include "ConstantDecl.h"

StoryWindow::StoryWindow(SDL_Renderer* gameRenderer) : WindowInterface()
{
	createWindowTexture(gameRenderer);
}

void StoryWindow::createWindowTexture(SDL_Renderer* gameRenderer)
{
	SDL_Surface* tmpSurface = IMG_Load("../../resources/images/story_window.jpg");
	this->windowTexture = SDL_CreateTextureFromSurface(gameRenderer, tmpSurface);
	this->windowTextureRenderingPos = { 0, 0, GAME_WINDOW::WIDTH, GAME_WINDOW::HEIGHT };
	SDL_FreeSurface(tmpSurface);
}

void StoryWindow::renderWindow(SDL_Renderer* gameRenderer, const int& xPos, const int& yPos)
{
	SDL_RenderCopy(gameRenderer, this->windowTexture, &(this->windowTextureRenderingPos), &(this->windowTextureRenderingPos));
}

ButtonType StoryWindow::getSeletedButtonTypeInWindow(const int& xPos, const int& yPos)
{
	return NO_RETURN_TYPE;
}

StoryWindow::~StoryWindow()
{
	SDL_DestroyTexture(this->windowTexture);
}

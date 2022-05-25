#include "WaringWindow.h"


WaringWindow::WaringWindow(SDL_Renderer* gameRenderer, const std::string& textInWindow)
{
	SDL_Color fontColor = { 255, 255, 255, 0 };

	//this->windowFont = TTF_OpenFont("../../resources/fonts/waring_window.ttf", 30);
	//SDL_Surface* tmpSurface = TTF_RenderUTF8_Blended(this->windowFont, CW2A((L"sdad"), CP_UTF8), fontColor);
	//this->fontTexture = SDL_CreateTextureFromSurface(gameRenderer, tmpSurface);
	//SDL_FreeSurface(tmpSurface);
	//createWindow(gameRenderer);

}

void WaringWindow::createWindow(SDL_Renderer* gameRenderer)
{
	SDL_Surface* tmpSurface = IMG_Load("../../resources/images/warning_window.png");
	this->windowTexture = SDL_CreateTextureFromSurface(gameRenderer, tmpSurface);
	this->windowTextureRenderingPos = { 0, 0, GAME_WINDOW::WIDTH, GAME_WINDOW::HEIGHT };
	SDL_FreeSurface(tmpSurface);
}

void WaringWindow::AddButton(RectangleButton& _button)
{
	this->windowButton.push_back(_button);
}

bool WaringWindow::isViewingWindow() const
{
	return this->windowView;
}

void WaringWindow::setWindowView(bool _windowView)
{
	this->windowView = _windowView;
}

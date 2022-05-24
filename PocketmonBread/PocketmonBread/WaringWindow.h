#pragma once

#include "SDL_ttf.h"
#include "RectangleButton.h"
#include <windows.h>
#include <atlstr.h>
#include <string>

class WaringWindow
{
private:
	SDL_Texture* windowTexture;
	SDL_Texture* fontTexture;
	SDL_Rect windowTexturePos;
	SDL_Rect windowTextureRenderingPos;
	RectangleButton * cancelButton, trueButton, falseButton;
	TTF_Font* windowFont;
	Mix_Chunk* buttonEffectSound;

public:
	explicit WaringWindow(const std::string& textInWindow);


}
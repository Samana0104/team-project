#pragma once

#include "SDL_ttf.h"
#include "SDL_image.h"
#include "RectangleButton.h"
#include "ConstantDecl.h"
#include <vector>
#include <windows.h>
#include <atlstr.h>
#include <string>

namespace WINDOW_BUTTON
{
	enum TYPE
	{
		EXIT = 0,
		BUTTON_1,
		BUTTON_2,
		BUTTON_3,
		BUTTON_4,
		BUTTON_5
	};
};

class WaringWindow
{
private:
	SDL_Texture* windowTexture;
	SDL_Texture* fontTexture;
	SDL_Rect windowTexturePos;
	SDL_Rect windowTextureRenderingPos;
	std::vector<RectangleButton> windowButton;
	TTF_Font* windowFont;
	Mix_Chunk* buttonEffectSound;
	bool windowView = false;

	void createWindow(SDL_Renderer* gameRenderer);
public:
	explicit WaringWindow(SDL_Renderer* gameRenderer, const std::string& textInWindow);

	void AddButton(RectangleButton& _button);
	bool isViewingWindow() const;
	void setWindowView(bool _windowView);
};
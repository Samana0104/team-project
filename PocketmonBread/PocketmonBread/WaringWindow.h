#pragma once

#include "SDL_ttf.h"
#include "SDL_image.h"
#include "RectangleButton.h"
#include "TTFTextManger.h"
#include "WindowInterface.h"
#include <vector>

namespace WARING_BUTTON
{
	enum TYPE
	{
		REFUSING= 0,
		CONSENTING = 1,
		COUNT = 2
	};
}

class WaringWindow : public WindowInterface
{
private:
	SDL_Texture* windowTexture;
	SDL_Rect windowTextureRenderingPos;
	RectangleButton * windowButtons[WARING_BUTTON::COUNT];
	std::vector<TTFTextManger*> windowTexts;
	Mix_Chunk* buttonEffectSound;

	void createWindowTexture(SDL_Renderer* gameRenderer);
	void createButton(SDL_Renderer* gameRenderer);
	void renderText(SDL_Renderer* gameRenderer);
	void renderButtons(SDL_Renderer* gameRenderer, const int& xPos, const int& yPos);
public:
	explicit WaringWindow(SDL_Renderer* gameRenderer);

	virtual ~WaringWindow();
	virtual void renderWindow(SDL_Renderer* gameRenderer, const int& xPos, const int& yPos);
	virtual ButtonType getSeletedButtonTypeInWindow(const int& xPos, const int& yPos);

	void addText(SDL_Renderer* gameRenderer, const std::string& text, int textYPos);
};
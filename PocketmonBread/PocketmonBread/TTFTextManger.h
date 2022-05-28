#pragma once

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include <string>
#include <windows.h>
#include <atlstr.h>

class TTFTextManger
{
private:
	TTF_Font* font;
	SDL_Texture* textTexture;
	SDL_Rect textTextureRenderingPos;
	SDL_Color textColor;
	std::string text;

	void createTextTexture(SDL_Renderer* gameRenderer);
public:
	explicit TTFTextManger(SDL_Renderer* gameRenderer, const std::string _text, TTF_Font* _font, const SDL_Rect& _textTextureRenderingPos, const SDL_Color& _textColor);
	~TTFTextManger();

	void setTextColor(const SDL_Color& _textColor);
	void setTextTextureRenderingPos(const SDL_Rect& _textTextureRenderingPos);
	const SDL_Rect& getTextTextureRenderingPos() const;
	void setText(const std::string _text, SDL_Renderer* gameRenderer);
	void renderTextTexture(SDL_Renderer* gameRenderer);
};
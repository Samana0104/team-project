#include "TTFTextManger.h"


TTFTextManger::TTFTextManger(SDL_Renderer* gameRenderer, const std::string _text, TTF_Font* _font, const SDL_Rect& _textTextureRenderingPos, const SDL_Color& _textColor)
	: text(_text), font(_font), textTextureRenderingPos(_textTextureRenderingPos), textColor(_textColor)
{
	createTextTexture(gameRenderer);
}

void TTFTextManger::createTextTexture(SDL_Renderer* gameRenderer)
{
	if (this->textTexture != NULL)
		SDL_DestroyTexture(this->textTexture);

	wchar_t strUnicode[256] = { 0, }; 
	char strMultibyte[256] = { 0, }; 
	strcpy_s(strMultibyte, 256, this->text.c_str()); 
	int nLen = MultiByteToWideChar(CP_ACP, 0, strMultibyte, strlen(strMultibyte), NULL, NULL); 
	MultiByteToWideChar(CP_ACP, 0, strMultibyte, strlen(strMultibyte), strUnicode, nLen); 
	/* 
	해당 코드의 출처 https://hizstory.tistory.com/9 
	멀티바이트 -> 유니코드 변환
	*/

	SDL_Surface* tmpSurface = TTF_RenderUTF8_Blended(this->font, CW2A(strUnicode, CP_UTF8), this->textColor);
	this->textTextureRenderingPos.w = tmpSurface->w;
	this->textTextureRenderingPos.h = tmpSurface->h;
	this->textTexture = SDL_CreateTextureFromSurface(gameRenderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);	
}

void TTFTextManger::setTextColor(const SDL_Color& _textColor)
{
	this->textColor = _textColor;
}

void TTFTextManger::setTextTextureRenderingPos(const SDL_Rect& _textTextureRenderingPos)
{
	this->textTextureRenderingPos = _textTextureRenderingPos;
}

const SDL_Rect& TTFTextManger::getTextTextureRenderingPos() const
{
	return this->textTextureRenderingPos;
}

void TTFTextManger::setText(const std::string _text, SDL_Renderer* gameRenderer)
{
	this->text = _text;
	createTextTexture(gameRenderer);
}

void TTFTextManger::renderTextTexture(SDL_Renderer* gameRenderer)
{
	SDL_RenderCopy(gameRenderer, this->textTexture, NULL, &(this->textTextureRenderingPos));
}

TTFTextManger::~TTFTextManger()
{
	SDL_DestroyTexture(this->textTexture);
	TTF_CloseFont(this->font);
}

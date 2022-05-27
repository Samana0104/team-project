#pragma once

#include "SDL.h"
#include "SDL_image.h"

typedef int ButtonType;

const int NO_RETURN_TYPE = -1;

class WindowInterface
{
private:
	bool isViewWindowe = false;
	SDL_Cursor* mouseArrowCursor;
	SDL_Cursor* mouseHandCursor;
protected:
	explicit WindowInterface() 
	{
		this->mouseArrowCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
		this->mouseHandCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	}
public:
	virtual ~WindowInterface() 
	{ 
		SDL_FreeCursor(this->mouseArrowCursor);
		SDL_FreeCursor(this->mouseHandCursor);
	}

	virtual void renderWindow(SDL_Renderer* gameRanderer, const int& xPos, const int& yPos) = 0;
	virtual ButtonType getSeletedButtonTypeInWindow(const int& xPos, const int& yPos) = 0;

	bool isViewingWindow() const { return this->isViewWindowe; }
	void setIsViewWindow(const bool& _isViewFrame) { this->isViewWindowe = _isViewFrame; }
	SDL_Cursor* getMouseArrowCursor() { return this->mouseArrowCursor; }
	SDL_Cursor* getMouseHandCursor() { return this->mouseHandCursor; }
};
#pragma once

#include "Player.h"
#include "SDL.h"
#include "SDL_image.h"

/*
* POCKETMON::SEAL�� Player.h�� ����
*/

const int RENDERING_MAX_POCKETMONT = 6; // ������ ���� ���ϸ� ��

class PocketmonSeal
{
private:
	SDL_Texture* pocketmonSealTextures[POCKETMON::COUNT];
	SDL_Texture* noPocketmonSealTexture;
	SDL_Rect pocketmonTexturePos;
	SDL_Rect pocketmonTextureRenderingPos[POCKETMON::COUNT];
	int presentCollectionPage = 1;

	void createPocketmonSealTextures(SDL_Renderer* gameRenderer);
public:
	explicit PocketmonSeal(SDL_Renderer* gameRenderer);
	~PocketmonSeal();

	void ChangeNextCollectionPage();
	void ChangeFormerCollectionPage();
	void renderPocketmonSeal(SDL_Renderer* gameRenderer, Player * _player);
	SDL_Texture* getPocketmonSealTextures(const POCKETMON::SEAL& pocketmonType);
	int getPresentCollectionPage() const;
};

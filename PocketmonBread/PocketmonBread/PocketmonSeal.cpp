#include "PocketmonSeal.h"

PocketmonSeal::PocketmonSeal(SDL_Renderer* gameRenderer)
{
	createPocketmonSealTextures(gameRenderer);
}

void PocketmonSeal::createPocketmonSealTextures(SDL_Renderer* gameRenderer)
{
	this->pocketmonTexturePos = { 0, 0, 270, 300 };

	SDL_Surface* tmpSurface = IMG_Load("../../resources/images/seals/001.png");
	this->pocketmonSealTextures[POCKETMON::TYPE_1] = SDL_CreateTextureFromSurface(gameRenderer, tmpSurface);
	this->pocketmonTextureRenderingPos[POCKETMON::TYPE_1] = { 460, 130, 270, 300 };
	SDL_FreeSurface(tmpSurface);

	tmpSurface = IMG_Load("../../resources/images/seals/002.png");
	this->pocketmonSealTextures[POCKETMON::TYPE_2] = SDL_CreateTextureFromSurface(gameRenderer, tmpSurface);
	this->pocketmonTextureRenderingPos[POCKETMON::TYPE_2] = { 798, 130, 270, 300 };
	SDL_FreeSurface(tmpSurface);

	tmpSurface = IMG_Load("../../resources/images/seals/003.png");
	this->pocketmonSealTextures[POCKETMON::TYPE_3] = SDL_CreateTextureFromSurface(gameRenderer, tmpSurface);
	this->pocketmonTextureRenderingPos[POCKETMON::TYPE_3] = { 1136, 130, 270, 300 };
	SDL_FreeSurface(tmpSurface);

	tmpSurface = IMG_Load("../../resources/images/seals/004.png");
	this->pocketmonSealTextures[POCKETMON::TYPE_4] = SDL_CreateTextureFromSurface(gameRenderer, tmpSurface);
	this->pocketmonTextureRenderingPos[POCKETMON::TYPE_4] = { 460, 473, 270, 300 };
	SDL_FreeSurface(tmpSurface);

	tmpSurface = IMG_Load("../../resources/images/seals/005.png");
	this->pocketmonSealTextures[POCKETMON::TYPE_5] = SDL_CreateTextureFromSurface(gameRenderer, tmpSurface);
	this->pocketmonTextureRenderingPos[POCKETMON::TYPE_5] = { 798, 473, 270, 300 };
	SDL_FreeSurface(tmpSurface);

	tmpSurface = IMG_Load("../../resources/images/seals/006.png");
	this->pocketmonSealTextures[POCKETMON::TYPE_6] = SDL_CreateTextureFromSurface(gameRenderer, tmpSurface);
	this->pocketmonTextureRenderingPos[POCKETMON::TYPE_6] = { 1136, 473, 270, 300 };
	SDL_FreeSurface(tmpSurface);

	tmpSurface = IMG_Load("../../resources/images/seals/007.png");
	this->pocketmonSealTextures[POCKETMON::TYPE_7] = SDL_CreateTextureFromSurface(gameRenderer, tmpSurface);
	this->pocketmonTextureRenderingPos[POCKETMON::TYPE_7] = { 460, 130, 270, 300 };
	SDL_FreeSurface(tmpSurface);

	tmpSurface = IMG_Load("../../resources/images/seals/008.png");
	this->pocketmonSealTextures[POCKETMON::TYPE_8] = SDL_CreateTextureFromSurface(gameRenderer, tmpSurface);
	this->pocketmonTextureRenderingPos[POCKETMON::TYPE_8] = { 798, 130, 270, 300 };
	SDL_FreeSurface(tmpSurface);

	tmpSurface = IMG_Load("../../resources/images/seals/009.png");
	this->pocketmonSealTextures[POCKETMON::TYPE_9] = SDL_CreateTextureFromSurface(gameRenderer, tmpSurface);
	this->pocketmonTextureRenderingPos[POCKETMON::TYPE_9] = { 1136, 130, 270, 300 };
	SDL_FreeSurface(tmpSurface);

	tmpSurface = IMG_Load("../../resources/images/seals/010.png");
	this->pocketmonSealTextures[POCKETMON::TYPE_10] = SDL_CreateTextureFromSurface(gameRenderer, tmpSurface);
	this->pocketmonTextureRenderingPos[POCKETMON::TYPE_10] = { 460, 473, 270, 300 };
	SDL_FreeSurface(tmpSurface);

	tmpSurface = IMG_Load("../../resources/images/seals/011.png");
	this->pocketmonSealTextures[POCKETMON::TYPE_11] = SDL_CreateTextureFromSurface(gameRenderer, tmpSurface);
	this->pocketmonTextureRenderingPos[POCKETMON::TYPE_11] = { 798, 473, 270, 300 };
	SDL_FreeSurface(tmpSurface);

	tmpSurface = IMG_Load("../../resources/images/seals/012.png");
	this->pocketmonSealTextures[POCKETMON::TYPE_12] = SDL_CreateTextureFromSurface(gameRenderer, tmpSurface);
	this->pocketmonTextureRenderingPos[POCKETMON::TYPE_12] = { 1136, 473, 270, 300 };
	SDL_FreeSurface(tmpSurface);

	tmpSurface = IMG_Load("../../resources/images/seals/seal_question.png");
	this->noPocketmonSealTexture = SDL_CreateTextureFromSurface(gameRenderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
}

void PocketmonSeal::ChangeNextCollectionPage()
{
	if (this->presentCollectionPage * RENDERING_MAX_POCKETMONT < POCKETMON::COUNT)
		this->presentCollectionPage++;
}

void PocketmonSeal::ChangeFormerCollectionPage()
{
	if ((this->presentCollectionPage-1) * RENDERING_MAX_POCKETMONT > 0)
		this->presentCollectionPage--;
}

void PocketmonSeal::renderPocketmonSeal(SDL_Renderer* gameRenderer, Player* player)
{
	for (int i = this->presentCollectionPage-1; i < presentCollectionPage * RENDERING_MAX_POCKETMONT; i++)
	{
		if(player->hasPocketmonSeal(static_cast<POCKETMON::SEAL>(i)))
			SDL_RenderCopy(gameRenderer, this->pocketmonSealTextures[i], &(this->pocketmonTexturePos), &(this->pocketmonTextureRenderingPos[i]));
		else
			SDL_RenderCopy(gameRenderer, this->noPocketmonSealTexture, &(this->pocketmonTexturePos), &(this->pocketmonTextureRenderingPos[i]));
	}
}

SDL_Texture* PocketmonSeal::getPocketmonSealTextures(const POCKETMON::SEAL& pocketmonType)
{
	return this->pocketmonSealTextures[pocketmonType];
}

int PocketmonSeal::getPresentCollectionPage() const
{
	return this->presentCollectionPage;
}

PocketmonSeal::~PocketmonSeal()
{
	for (int i = 0; i < POCKETMON::COUNT; i++)
		SDL_DestroyTexture(this->pocketmonSealTextures[i]);

	SDL_DestroyTexture(this->noPocketmonSealTexture);
}



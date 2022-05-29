#include "Player.h"

Player::Player()
{
}

bool Player::hasPocketmonSeal(const POCKETMON::SEAL& sealType)
{
    return this->obtainedPocketmon[sealType];
}

void Player::playerClearedStage1()
{
    this->clearedStage1 = true;
    this->obtainedBread += 3;
}

void Player::playerClearedStage2()
{
    this->clearedStage2 = true;
    this->obtainedBread += 5;
}

void Player::playerClearedStage3()
{
    this->obtainedBread += 7;
}


void Player::applyPlayerCheatMode()
{
    this->obtainedBread = 500;
    this->clearedStage1 = true;
    this->clearedStage2 = true;
    
    for (int i = 0; i < POCKETMON::COUNT; i++)
        this->obtainedPocketmon[i] = true;
}

int Player::getObtainedBread() const
{
    return this->obtainedBread;
}

int Player::getPocketmonSealCount() const
{
    int count = 0;

    for (int i = 0; i < POCKETMON::COUNT; i++)
    {
        if (this->obtainedPocketmon[i])
            count++;
    }

    return count;
}

void Player::obtainPocketmonSeal(const POCKETMON::SEAL& pocketmonType)
{
    this->obtainedPocketmon[pocketmonType] = true;
}

void Player::usePocketmonBread()
{
    this->obtainedBread -= 1;
}

bool Player::isStage1Cleared() const
{
    return this->clearedStage1;
}

bool Player::isStage2Cleared() const
{
    return this->clearedStage2;
}

bool Player::isEndingViewed() const
{
    return this->viewingEnding;
}

void Player::setViewingEnding(bool view)
{
    this->viewingEnding = view;
}

Player::~Player()
{
}

#include "DelayTimer.h"

DelayTimer::DelayTimer(const double& _timerForDelay) : timeForDelay(_timerForDelay), timeForCalculationOfDelay(_timerForDelay)
{
}

bool DelayTimer::isDelaying()
{
	if (this->timeForCalculationOfDelay <= 0.0)
	{
		this->timeForCalculationOfDelay = this->timeForDelay;
		return false;
	}
	else
	{
		return true;
	}
}

void DelayTimer::decreaseTime(const double& time)
{
	this->timeForCalculationOfDelay -= time;
}

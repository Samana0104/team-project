#pragma once

class DelayTimer
{
private:
	double timeForDelay;
	double timeForCalculationOfDelay;
public:
	explicit DelayTimer(const double& _timerForDelay);

	bool isDelaying();
	void decreaseTime(const double& time);
};
#include "chQTimer.h"

chQTimer::chQTimer(void)
{
	LARGE_INTEGER f;
	QueryPerformanceFrequency(&f);
	this->freq = 1.0f/(float)f.QuadPart;
	QueryPerformanceCounter(&this->prevTime);
}

chQTimer::~chQTimer(void)
{
}

float chQTimer::getTimeElapsed_float()
{
	QueryPerformanceCounter(&this->currTime);
	this->timeElapsed = ((float)(this->currTime.QuadPart - this->prevTime.QuadPart)*this->freq);
	this->prevTime = this->currTime;
	return this->timeElapsed;
}

char* chQTimer::getTimeElapsed()
{
	char data[128];
	this->getTimeElapsed_float();
	printf("%g",&this->timeElapsed);
	return data;
}

void chQTimer::reset()
{
	this->getTimeElapsed_float();
	this->timeElapsed = 0.0f;
}
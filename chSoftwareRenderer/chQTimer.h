#pragma once

#include <windows.h>
#include <stdio.h>

class chQTimer
{
public:
	chQTimer(void);
	~chQTimer(void);

	char* getTimeElapsed();
	float getTimeElapsed_float();
	void reset();

private:
	LARGE_INTEGER prevTime,currTime;
	float timeElapsed,freq;

};

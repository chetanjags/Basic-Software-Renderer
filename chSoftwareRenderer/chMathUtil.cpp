#include "chMathUtil.h"
#include <math.h>
#include "chVector3.h"

//get in -pi to pi range

float chWrapPi(float rads)
{
	if(rads >= -CH_PI && rads<= CH_PI)
	{
		return rads;
	}

	rads += CH_PI;
	rads -= floor(rads*CH_1overPI*0.5f)*CH_2PI;
	rads -= CH_PI;

	return rads;
}


bool chIsUnitVector(const chVector3* vec)
{
	float mag = vec->x*vec->x + vec->y*vec->y + vec->z*vec->z;
	if(fabs(mag-1.0f) < 0.001f)
		return true;
	else
		return false;
}
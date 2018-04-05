#pragma once

#ifndef __chMathUtil_H_Included__
#define __chMathUtil_H_Included__

#include <math.h>

const float CH_PI = 3.141592654f;
const float CH_2PI = 2.0f*CH_PI;
const float CH_1overPI = 1/CH_PI;
const float CH_PIover2 = CH_PI/2.0f;

const float CH_EPSILON = 0.0001f;
const float CH_INFINITY = 1e37f;

//some utility functions 


extern float chWrapPi(float rads);
inline float chDegToRad(float deg) { return deg * CH_PI/180; }
inline float chRadToDeg(float rad) { return rad * 180*CH_1overPI; }

inline float chSafeACos(float angle)
{
	if(angle<=-1.0f)
		return CH_PI;
	else
		if(angle>=1.0f)
			return 0.0f;
	
	return angle = acos(angle);
}

class chVector3;
extern bool chIsUnitVector(const chVector3* vec);

#endif
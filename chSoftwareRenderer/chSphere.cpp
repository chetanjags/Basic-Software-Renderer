#include "chSphere.h"

//chSphere::chSphere(void)
//{
//}
//
//chSphere::~chSphere(void)
//{
//}

void chSphere::create(const chVector3* sCenter,float rad)
{
	center = *sCenter;
	radius = rad;
}
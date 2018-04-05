#pragma once

#include "chVector3.h"

typedef class chPlane
{
public:
	chPlane(const chVector3* unitNormal,float distanceFromOrigin);
	chPlane(const chVector3* p0,const chVector3* p1,const chVector3* p2);
	~chPlane(void);

	void BestFitPlane(const chVector3 *listVec,int size);

	float DistanceFromPoint(const chVector3 *point)const;

	float operator *(const chVector3* vec)const;

	chVector3 normal;
	float d;

}chPlane,*LPChPlane;

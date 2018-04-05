#include "chPlane.h"
#include "chMathUtil.h"
#include "assert.h"

chPlane::chPlane(const chVector3* unitNormal,float distanceFromOrigin)
{
	assert(chIsUnitVector(unitNormal));
	this->normal = *unitNormal;
	this->d = distanceFromOrigin;
}

chPlane::chPlane(const chVector3* p0,const chVector3* p1,const chVector3* p2)
{
	chVector3 e0 = *p2 - *p1;
	chVector3 e2 = *p1 - *p0;

	chVector3 cross = chVec3Cross(&e2,&e0);

	float mag=0.0f;
	assert((mag=chVec3Magnitude(&cross)) > 0.0001f);

	this->normal = cross/mag;

	d = chVec3DotProduct(&normal,p1);
}

chPlane::~chPlane(void)
{
}

float chPlane::operator *(const chVector3 *vec) const
{
	return chVec3DotProduct(&normal,vec);
}

float chPlane::DistanceFromPoint(const chVector3 *point) const
{
	return (chVec3DotProduct(&normal,point) - d);
}


void chPlane::BestFitPlane(const chVector3 *listVec, int size)
{
	int i=0;

	const chVector3 *vec1 = &listVec[size-1];
	
	normal.x = 0.0f;
	normal.y = 0.0f;
	normal.z = 0.0f;

	for(i=0;i<size;i++)
	{
		const chVector3 *vec2 = &listVec[i];
		normal.x = (vec1->z + vec2->z)*(vec1->y - vec2->y);
		normal.y = (vec1->z - vec2->z)*(vec1->x + vec2->x);
		normal.z = (vec1->x - vec2->x)*(vec1->y + vec2->y);

		vec1 = vec2;
		vec2 = 0;
	}
	vec1 = 0;

	normal = chVec3Normalize(&normal);

	d=0.0f;
	for(i=0;i<size;i++)
	{
		d+=chVec3DotProduct(&normal,&listVec[i]);
	}

	d=d/size;

}
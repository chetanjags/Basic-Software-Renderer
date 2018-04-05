#include "chCollisionTests.h"
#include "chPlane.h"
#include "chRay.h"

bool chCollisionTests::PlaneRay(chVector3 *result,const chPlane *plane, const chRay *ray)
{
	*result = CH_ZeroVector;
	float t = chVec3DotProduct(&plane->normal,&ray->d);

	if(t<=0.0001f || t>ray->t)
		return false;

	*result = ray->p0 + ray->d*t;

	return true;
}
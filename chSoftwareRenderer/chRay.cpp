#include "chRay.h"
#include "chMathUtil.h"
#include "assert.h"

chRay::chRay(const chVector3 *startPoint,const chVector3 *unitDirection,float length)
{
	assert(chIsUnitVector(unitDirection));

	this->p0 = *startPoint;
	this->d = *unitDirection;
	this->t = length;
}

chRay::~chRay(void)
{
}

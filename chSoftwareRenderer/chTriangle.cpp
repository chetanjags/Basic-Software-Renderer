#include "chTriangle.h"
#include "chMathUtil.h"
#include "assert.h"

chTriangle::chTriangle(const chVector3* v1,const chVector3* v2, const chVector3* v3,bool isComputeNormal)
{
	verts[0] = *v1;
	verts[1] = *v2;
	verts[2] = *v3;

	if(isComputeNormal)
		ComputeNormal();
}

chTriangle::~chTriangle(void)
{
}


void chTriangle::ComputeNormal()
{
	chVector3 e1 = verts[2]-verts[1];
	chVector3 e2 = verts[0]-verts[2];

	normal = chVec3Cross(&e1,&e2);

	assert(chIsUnitVector(&normal));
	normal = chVec3Normalize(&normal);
}
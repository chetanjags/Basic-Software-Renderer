#pragma once

#include "chTriangle.h"

typedef class chTriangleMesh
{
public:
	chTriangleMesh(void);
	~chTriangleMesh(void);

	chTriangle* triangleList;
	int count;

}chTriangleMesh,*LPChTriangleMesh;

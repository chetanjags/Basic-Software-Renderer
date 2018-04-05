#pragma once

#include "chVector3.h"

typedef class chTriangle
{
public:
	chTriangle(const chVector3* v1,const chVector3* v2, const chVector3* v3,bool isComputeNormal);
	~chTriangle(void);

	chVector3 verts[3];
	chVector3 normal;

	void ComputeNormal();

	float operator*(const chVector3* vec)const;

}chTriangle,*LPChTriangle;

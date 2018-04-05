#pragma once

#include "chVector3.h"

typedef class chAABB3
{
public:
	chAABB3(void);
	~chAABB3(void);

	chAABB3(const chVector3* position,float width,float height,float depth);
	chAABB3(const chVector3* vec1,const chVector3 *vec2);
	
	void AddPoint(const chVector3 *point);

	void empty();

	float getHeight();
	float getWidth();
	float getDepth();

private:
	chVector3 min,max;

}chAABB3,*LPChAABB3;

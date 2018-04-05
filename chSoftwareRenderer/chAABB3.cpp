#include "chAABB3.h"
#include "chMathUtil.h"

chAABB3::chAABB3(void)
{
	empty();
}

chAABB3::~chAABB3(void)
{
}


void chAABB3::empty()
{
	min.x = min.y = min.z = CH_INFINITY;
	max.x = max.y = max.z = -CH_INFINITY;
}

chAABB3::chAABB3(const chVector3 *position, float width, float height, float depth)
{

	min.x = position->x - width;
	min.y = position->y - height;
	min.z = position->z - depth;

	max.x = position->x + width;
	max.y = position->y + height;
	max.z = position->z + depth;

}


chAABB3::chAABB3(const chVector3* vec1,const chVector3 *vec2)
{
	if(vec1->x < vec2->x)
	{
		min.x = vec1->x;
		max.x = vec2->x;
	}
	else
	{
		min.x = vec2->x;
		max.x = vec1->x;
	}

	if(vec1->y < vec2->y)
	{
		min.y = vec1->y;
		max.y = vec2->y;
	}
	else
	{
		min.y = vec2->y;
		max.y = vec1->y;
	}

	if(vec1->z < vec2->z)
	{
		min.z = vec1->z;
		max.z = vec2->z;
	}
	else
	{
		min.z = vec2->z;
		max.z = vec1->z;
	}

}


void chAABB3::AddPoint(const chVector3 *point)
{
	if (point->x < min.x) min.x = point->x;
	if (point->x > max.x) max.x = point->x;
	if (point->y < min.x) min.y = point->y;
	if (point->y > max.x) max.y = point->y;
	if (point->z < min.x) min.z = point->z;
	if (point->z > max.x) max.z = point->z;

}

float chAABB3::getWidth()
{
	return max.x - min.x;
}

float chAABB3::getHeight()
{
	return max.y - min.y;
}

float chAABB3::getDepth()
{
	return max.z - min.z;
}
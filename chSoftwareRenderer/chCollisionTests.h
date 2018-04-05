#pragma once

class chVector3;
class chRay;
class chPlane;

class chCollisionTests
{
public:

	static bool PlaneRay(chVector3* result,const chPlane* plane,const chRay* ray);

};

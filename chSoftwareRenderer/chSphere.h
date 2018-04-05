#pragma once

#include "chVector3.h"

typedef class chSphere
{
public:
	//chSphere(void);
	//~chSphere(void);

	void create(const chVector3* sCenter,float rad);

	chVector3 center;
	float radius;

}chSphere,*LPChSphere;

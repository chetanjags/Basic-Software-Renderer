#pragma once

#ifndef __chRay_H_Included__
#define __chRay_H_Included__

#include "chVector3.h"

class chVector3;

typedef class chRay
{
public:
	chRay(const chVector3 *startPoint,const chVector3 *unitDirection,float length);
	~chRay(void);

	chVector3 p0;
	chVector3 d;
	float t;

}chRay,*LPChRay;


#endif
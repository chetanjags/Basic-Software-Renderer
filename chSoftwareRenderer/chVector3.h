#pragma once


#ifndef __chVector3_H_Inluded__
#define __chVector3_H_Inluded__


#include "chMacros.h"
#include <math.h>

typedef class chVector3
{
public:
	chVector3(void)
	{x=0.0f; y=0.0f; z=0.0f;}
	chVector3(float nx,float ny,float nz):x(nx),y(ny),z(nz)
	{}
	chVector3(const chVector3& a):x(a.x),y(a.y),z(a.z)
	{}

	~chVector3(void)
	{}

	//data members
	float x,y,z;
	//float w;

	////member functions

	void Zero()
	{
		x=0;
		y=0;
		z=0;
	}

	//operators

	chVector3& operator=(const chVector3& a)
	{
		x=a.x;
		y=a.y;
		z=a.z;
		return *this;
	}

	bool operator ==(const chVector3& a)const
	{
		return (x==a.x && y==a.y && z==a.z);
	}

	bool operator !=(const chVector3& a)const
	{
		return !(x==a.x && y==a.y && z==a.z);
	}

	chVector3 operator-() const
	{
		return chVector3(-x,-y,-z);
	}

	chVector3 operator+(const chVector3& a) const
	{
		return chVector3(x+a.x,y+a.y,z+a.z);
	}

	chVector3 operator-(const chVector3& a) const
	{
		return chVector3(x-a.x,y-a.y,z-a.z);
	}
	
	chVector3& operator+=(const chVector3& a)
	{
		x+= a.x;
		y+=a.y;
		z+=a.z;

		return *(this);
	}

	chVector3& operator-=(const chVector3& a)
	{
		x-= a.x;
		y-=a.y;
		z-=a.z;

		return *(this);
	}
	
	chVector3 operator*(float a)const
	{
		return chVector3(x*a,y*a,z*a);
	}

	chVector3 operator/(float a)const
	{
		return chVector3(x/a,y/a,z/a);
	}

	chVector3& operator*=(float a)
	{
		x*=a;
		y*=a;
		z*=a;
		return *this;
	}

	chVector3& operator/=(float a)
	{
		x/=a;
		y/=a;
		z/=a;
		return *this;
	}

	chVector3 operator*(const chVector3& a)const
	{
		return chVector3(x*a.x , y*a.y , z*a.z);
	}

	chVector3& operator*=(const chVector3 a)
	{
		x*=a.x ;
		y*=a.y ;
		z*=a.z;

		return *this;
	}


}chVector3,*LPChVector3;


const chVector3 CH_ZeroVector(0.0f,0.0f,0.0f);

//non member functions


inline float chVec3Magnitude(const chVector3* a)
{
	return sqrt(a->x*a->x + a->y*a->y + a->z*a->z);
}

inline chVector3 chVec3Normalize(const chVector3* a)
{
	float mag = sqrt(a->x*a->x + a->y*a->y + a->z*a->z);
	
	if(mag<=0.0f)
		return chVector3(0,0,0);

	return chVector3(a->x/mag,a->y/mag,a->z/mag);
}

inline float chVec3DotProduct(const chVector3* a,const chVector3* b)
{
	return (a->x*b->x + a->y*b->y + a->z*b->z);
}

inline chVector3 chVec3Cross(const chVector3* a,const chVector3* b)
{
	return chVector3(a->y * b->z - a->z*b->y ,a->z * b->x - a->x * b->z , a->x * b->y - a->y * b->x);
}

inline float chVec3Distance(const chVector3* a,const chVector3* b)
{
	float dx = a->x - b->x;
	float dy = a->y - b->y;
	float dz = a->z - b->z;
	return sqrt(dx*dx + dy*dy + dz*dz);
}

#endif
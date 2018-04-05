#pragma once

#ifndef __chEulerAngles_H_Included__
#define __chEulerAngles_H_Included__

#include <math.h>

class chMatrix;
class chQuaternion;

typedef class chEulerAngles
{
public:

	//data members

	float heading,pitch,bank;


	chEulerAngles(void): heading(0.0f), pitch(0.0f),bank(0.0f){}

	chEulerAngles(float h,float p,float b) :heading(h),pitch(p),bank(b){}

	~chEulerAngles(void){}


	void canonize();

	//Get Euler angles from matrix form

	void FromWorldToObjectMatrix(const chMatrix* mat);
	void FromObjectToWorldMatrix(const chMatrix* mat);

	//Get Euler angles from quaternion form

	void FromInertialToObjectQuaternion(const chQuaternion* q);
	void FromObjectToInertialQuaternion(const chQuaternion* q);

}chEulerAngles,*LPChEulerAngles;




#endif
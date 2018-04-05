#pragma once


#ifndef __chQuaternion_H_Included__
#define __chQuaternion_H_Included__

class chVector3;
class chEulerAngles;

typedef class chQuaternion
{
public:

	float w,x,y,z;

	chQuaternion(void) {Identity();}
	chQuaternion(float _w,float _x,float _y,float _z): w(_w),x(_x),y(_y),z(_z) {}
	~chQuaternion(void){}

	void Identity() 
	{
		w = 1.0f;
		x=y=z=0.0f;
	}

	void SetRotationX(float angle);
	void SetRotationY(float angle);
	void SetRotationZ(float angle);
	void SetRotationAxis(const chVector3* axis,float angle);

	void SetRotationObjectToInertial(const chEulerAngles* eAngle);
	void SetRotationInertialToObject(const chEulerAngles* eAngle);

	//cross product
	chQuaternion operator* (const chQuaternion& a)const;
	chQuaternion& operator *= (const chQuaternion& a);

	void normalize();

	float GetRotationAngle() const;
	chVector3 GetRotationAxis() const;

}chQuaternion,*LPChQuaternion;

extern const chQuaternion CH_QuaternionIdentity;

extern float chQuaternionDotProduct(const chQuaternion* q1,const chQuaternion* q2);

extern chQuaternion chQuaternionSlerp(chQuaternion* q1,const chQuaternion* q2,float t);

extern chQuaternion chQuaternionConjugate(const chQuaternion* q1);

extern  chQuaternion chQuaternionPow(const chQuaternion* q1,float p);

#endif
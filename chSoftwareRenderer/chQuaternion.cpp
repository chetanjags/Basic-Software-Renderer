#include "chQuaternion.h"
#include "chVector3.h"
#include "chEulerAngles.h"
#include <assert.h>
#include "chMathUtil.h"


const chQuaternion CH_QuaternionIdentity (1.0f,0.0f,0.0f,0.0f);


void chQuaternion::SetRotationX(float angle)
{
	w = cos(angle/2.0f);
	x = sin(angle/2.0f);
	y=z=0.0f;
}

void chQuaternion::SetRotationY(float angle)
{
	angle /=2.0f;
	w = cos(angle);
	y = sin(angle);
	x=z=0.0f;
}

void chQuaternion::SetRotationZ(float angle)
{
	w = cos(angle/2.0f);
	z = sin(angle/2.0f);
	y=x=0.0f;
}

void chQuaternion::SetRotationAxis(const chVector3 *axis, float angle)
{
	assert(chIsUnitVector(axis));

	float s = sin(angle/2.0f);

	w = cos(angle/2.0f);
	x = axis->x * s;
	y = axis->y * s;
	z = axis->z * s;

}

void chQuaternion::SetRotationObjectToInertial(const chEulerAngles *eAngle)
{
	float sp,sb,sh;
	float cp,cb,ch;

	sp = sin(eAngle->pitch/2.0f);
	cp = cos(eAngle->pitch/2.0f);

	sb = sin(eAngle->bank/2.0f);
	cb = cos(eAngle->bank/2.0f);

	sh = sin(eAngle->heading/2.0f);
	ch = cos(eAngle->heading/2.0f);

	w = ch*cp*cb + sh*sp*sb;
	x = ch*sp*cb + sh*cp*sb;
	y = - ch*sp*sb + sh*cp*cb;
	z =  - sh*sp*cb + ch*cp*sb;

}

void chQuaternion::SetRotationInertialToObject(const chEulerAngles *eAngle)
{
	float sp,sb,sh;
	float cp,cb,ch;

	sp = sin(eAngle->pitch/2.0f);
	cp = cos(eAngle->pitch/2.0f);

	sb = sin(eAngle->bank/2.0f);
	cb = cos(eAngle->bank/2.0f);

	sh = sin(eAngle->heading/2.0f);
	ch = cos(eAngle->heading/2.0f);

	w = ch*cp*cb + sh*sp*sb;
	x = - ch*sp*cb - sh*cp*sb;
	y = ch*sp*sb - sh*cb*cp;
	z = sh*sp*cb - ch*cp*sb;

}


chQuaternion chQuaternion::operator *(const chQuaternion& a)const
{
	chQuaternion res;
	res.w = w*a.w - x*a.x - y*a.y - z*a.z;
	res.x = w*a.x + x*a.w + z*a.y - a.z*y;
	res.y = w*a.y + y*a.w + x*a.z - a.x*z;
	res.z = w*a.z + z*a.w + y*a.x - x*a.y;

	return res;
}


chQuaternion& chQuaternion::operator *=(const chQuaternion &a)
{
	w = w*a.w - x*a.x - y*a.y - z*a.z;
	x = w*a.x + x*a.w + z*a.y - a.z*y;
	y = w*a.y + y*a.w + x*a.z - a.x*z;
	z = w*a.z + z*a.w + y*a.x - x*a.y;

	return *(this);
}


void chQuaternion::normalize()
{
	float mag = sqrt(w*w + x*x + y*y + z*z);

	if(mag>0.0f)
	{
		w /= mag;
		x /= mag;
		y /= mag;
		z /= mag;
	}
	else
	{
		assert(false);
		this->Identity();
	}
}


float chQuaternion::GetRotationAngle() const
{
	float angle = 0.0f;
	angle = chSafeACos(w);
	return angle*2.0f;

}

chVector3 chQuaternion::GetRotationAxis() const
{
	float sangle = sin(this->GetRotationAngle()/2.0f);

	return chVector3(x/sangle,y/sangle,z/sangle);

}


float chQuaternionDotProduct(const chQuaternion* q1,const chQuaternion* q2)
{
	return (q1->w*q2->w + q1->x*q2->x + q1->y*q2->y + q1->z*q2->z);
}

chQuaternion chQuaternionSlerp(chQuaternion* q1,const chQuaternion* q2,float t)
{
	if(t>1.0f)
		return *q2;
	if(t<0.0f)
		return *q1;

	float cosw = chQuaternionDotProduct(q1,q2);
	float k0,k1;

	if(cosw < 0.0f)
	{
		cosw *= -1.0f;
		q1->w *= -1.0f;
		q1->x *= -1.0f;
		q1->y *= -1.0f;
		q1->z *= -1.0f;
	}

	if(cosw > 0.9999f)
	{
		k0 = 1.0f - t;
		k1 = t;
	}
	else
	{
		float sinw = sqrt(1-cosw*cosw);
		float w = atan2(sinw,cosw);

		k0 = sin((1.0f-t)*w)/sinw;
		k1 = sin(w*t)/sinw;
	}

	return chQuaternion(k0*q1->w+k1*q2->w,
		k0*q1->x + k1*q2->x,
		k0*q1->y + k1*q2->y,
		k0*q1->z + k1*q2->z );

}


chQuaternion chQuaternionConjugate(const chQuaternion* q1)
{
	return chQuaternion(q1->w, -q1->x, -q1->y, -q1->z);
}

chQuaternion chQuaternionPow(const  chQuaternion* q1,float p)
{
	if(fabs(q1->w) > 0.9999f)
		return *q1;

	float alpha = acos(q1->w);
	float newalpha = alpha*p;

	float mul = sin(newalpha)/sin(alpha);

	return chQuaternion(cos(newalpha), q1->x*mul, q1->y*mul, q1->z*mul);

}

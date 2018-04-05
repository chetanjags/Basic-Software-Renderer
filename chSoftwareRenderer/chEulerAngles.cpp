#include "chEulerAngles.h"
#include "chMathUtil.h"
#include "chMatrix.h"
#include "chQuaternion.h"


void chEulerAngles::FromWorldToObjectMatrix(const chMatrix *mat)
{
	float m23 = -mat->m23;

	if(fabs(m23)>0.9999f)
	{
		this->pitch = CH_PIover2 * ( m23 > 0.0f ? 1 : -1 );
		this->bank = 0;
		this->heading = atan2(-mat->m31,mat->m11);
	}
	else
	{
		this->pitch = asinf(m23);
		this->heading = atan2(mat->m13,mat->m33);
		this->bank = atan2(mat->m21,mat->m22);
	}

}


void chEulerAngles::FromObjectToWorldMatrix(const chMatrix *mat)
{

	float m32 = -mat->m32;

	if(fabs(m32)>0.9999f)
	{
		this->pitch = CH_PIover2 * ( m32 > 0.0f ? 1 : -1 );
		this->bank = 0;
		this->heading = atan2(-mat->m13,mat->m11);
	}
	else
	{
		this->pitch = asinf(m32);
		this->heading = atan2(mat->m31,mat->m33);
		this->bank = atan2(mat->m12,mat->m22);
	}

}

void chEulerAngles::FromInertialToObjectQuaternion(const chQuaternion *q)
{
	float sinp= -2.0f * (q->y*q->z + q->w*q->x);

	if(fabs(sinp) > 0.9999f)
	{
		this->pitch = CH_PIover2 * ( sinp > 0.0f ? 1 : -1 );
		this->bank = 0.0f;
		this->heading = atan2(-q->x*q->z - q->w*q->y,0.5f - q->y*q->y - q->z*q->z);
	}
	else
	{
		this->pitch = asin(sinp);
		this->heading = atan2( q->x*q->z - q->w*q->y,0.5f - q->x*q->x - q->y*q->y );
		this->bank = atan2( q->x*q->y - q->w*q->z,0.5f - q->x*q->x - q->z*q->z );
	}
}


void chEulerAngles::FromObjectToInertialQuaternion(const chQuaternion *q)
{
	float sinp= -2.0f * (q->y*q->z - q->w*q->x);

	if(fabs(sinp) > 0.9999f)
	{
		this->pitch = CH_PIover2 * ( sinp > 0.0f ? 1 : -1 );
		this->bank = 0.0f;
		this->heading = atan2(-q->x*q->z + q->w*q->y,0.5f - q->y*q->y - q->z*q->z);
	}
	else
	{
		this->pitch = asinf(sinp);
		this->heading = atan2( q->x*q->z + q->w*q->y,0.5f - q->x*q->x - q->y*q->y );
		this->bank = atan2( q->x*q->y + q->w*q->z,0.5f - q->x*q->x - q->z*q->z );
	}
}


void chEulerAngles::canonize()
{
	this->pitch = chWrapPi(this->pitch);

	if(this->pitch < -CH_PIover2)
	{
		this->pitch = - CH_PI - this->pitch;
		this->heading += CH_PI;
		this->bank += CH_PI;
	}
	else
		if(this->pitch > CH_PIover2)
		{
			this->pitch = CH_PI - this->pitch;
			this->heading += CH_PI;
			this->bank += CH_PI;
		}

		if(fabs(this->pitch) > (CH_PIover2-CH_EPSILON))
		{
			this->heading += bank;
			this->bank = 0.0f;
		}
		else
		{
			this->bank = chWrapPi(this->bank);
		}

		this->heading = chWrapPi(this->heading);

}
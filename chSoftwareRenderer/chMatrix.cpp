#include "chMatrix.h"
#include "math.h"
#include "chEulerAngles.h"
#include "chQuaternion.h"
#include "chVector3.h"
#include "assert.h"
#include "chMacros.h"
#include "chMathUtil.h"


void chMatrix::Identity()
{
	m11=m22=m33=m44=1.0f;
	m12=m13=m14=m21=m23=m24=m31=m32=m34=m41=m42=m43=0.0f;
}


void chMatrix::ZeroTransalation()
{
	m41=m42=m43=m14=m24=m34 = 0.0f;
	m44=1.0f;
}


void chMatrix::SetRotationEulerAnglesLW(const chEulerAngles *eAngle)
{
	float sh,ch,sb,cb,sp,cp;

	sp = sin(eAngle->pitch);
	cp = cos(eAngle->pitch);

	sb = sin(eAngle->bank);
	cb = cos(eAngle->bank);

	sh = sin(eAngle->heading);
	ch = cos(eAngle->heading);

	chMatrix m;

	m.m11 = ch * cb + sh * sp * sb;
	m.m12 = -ch * sb + sh * sp * cb;
	m.m13 = sh * cp;
	m.m21 = sb * cp;
	m.m22 = cb * cp;
	m.m23 = -sp;
	m.m31 = -sh * cb + ch * sp * sb;
	m.m32 = sb * sh + ch * sp * cb;
	m.m33 = ch * cp;

	ZeroTransalation();

	m11 = m.m11; m12 = m.m21; m13 = m.m31;
	m21 = m.m12; m22 = m.m22; m23 = m.m32;
	m31 = m.m13; m32 = m.m23; m33 = m.m33;

}


void chMatrix::SetRotationEulerAnglesWL(const chEulerAngles *eAngle)
{
	float sh,ch,sb,cb,sp,cp;

	sp = sin(eAngle->pitch);
	cp = cos(eAngle->pitch);

	sb = sin(eAngle->bank);
	cb = cos(eAngle->bank);

	sh = sin(eAngle->heading);
	ch = cos(eAngle->heading);

	ZeroTransalation();

	m11 = ch * cb + sh * sp * sb;
	m12 = -ch * sb + sh * sp * cb;
	m13 = sh * cp;
	m21 = sb * cp;
	m22 = cb * cp;
	m23 = -sp;
	m31 = -sh * cb + ch * sp * sb;
	m32 = sb * sh + ch * sp * cb;

}


void chMatrix::SetRotationQuaternion(const chQuaternion* q)
{
	float ww = 2.0f *q->w;
	float xx = 2.0f *q->x;
	float yy = 2.0f *q->y;
	float zz = 2.0f *q->z;

	ZeroTransalation();

	m11 = 1.0f - yy*q->y - zz*q->z;
	m12 = xx*q->y + ww*q->z;
	m13 = xx*q->z - ww*q->y;

	m21 = xx*q->y - ww*q->z;
	m22 = 1.0f - xx*q->x - zz*q->z;
	m23 = yy*q->z + ww*q->x;

	m31 = xx*q->z + ww*q->y;
	m32 = yy*q->z - ww*q->x;
	m33 = 1.0f - xx*q->x - yy*q->y;

}


void chMatrix::SetRotationX(float angle)
{
	float sa = sin(angle),ca=cos(angle);

	Identity();
	m22 = ca; m23 = sa;
	m32 = -sa; m33 = ca;
	ZeroTransalation();

}


void chMatrix::SetRotationY(float angle)
{
	float sa = sin(angle),ca=cos(angle);

	Identity();
	m11 = ca; m13 = -sa;
	m31 = sa; m33 = ca;
}


void chMatrix::SetRotationZ(float angle)
{
	float sa = sin(angle),ca=cos(angle);

	Identity();

	m11 = ca; m12 = sa;
	m21 = -sa; m22 = ca;
}


void chMatrix::SetRotationAxis(const chVector3 *axis, float angle)
{
	assert(chIsUnitVector(axis));

	float s=sin(angle),c=cos(angle);
	
	float a = 1.0f - c;
	float ax = a * axis->x;
	float ay = a * axis->y;
	float az = a * axis->z;
	
	m11 = ax*axis->x + c;
	m12 = ax*axis->y + axis->z*s;
	m13 = ax*axis->z - axis->y*s;
	m21 = ay*axis->x - axis->z*s;
	m22 = ay*axis->y + c;
	m23 = ay*axis->z + axis->x*s;
	m31 = az*axis->x + axis->y*s;
	m32 = az*axis->y - axis->x*s;
	m33 = az*axis->z + c;

	this->ZeroTransalation();
}


void chMatrix::SetTranslation(const chVector3 *vec)
{
	m41 = vec->x;
	m42 = vec->y;
	m43 = vec->z;
}

void chMatrix::SetTranslation(float x,float y,float z)
{
	m41 = x;
	m42 = y;
	m43 = z;
}


void chMatrix::SetScale(const chVector3 *scale)
{
	ZeroTransalation();
	m12=m13=m21=m23=m31=m32 = 0.0f;
	m11 = scale->x;
	m22 = scale->y;
	m33 = scale->z;
}


void chMatrix::SetScaleAlongAxis(const chVector3 *axis, float scale)
{
	assert(fabs(chVec3DotProduct(axis,axis) - 1.0f) < .01f);

	float a = scale - 1.0f;
	float ax = a * axis->x;
	float ay = a * axis->y;
	float az = a * axis->z;

	m11 = ax*axis->x + 1.0f;
	m22 = ay*axis->y + 1.0f;
	m32 = az*axis->z + 1.0f;
	m12 = m21 = ax*axis->y;
	m13 = m31 = ax*axis->z;
	m23 = m32 = ay*axis->z;

	ZeroTransalation();

}


void chMatrix::SetShearX(float s,float t)
{
	Identity();
	m12 = s;
	m13 = t;
}


void chMatrix::SetShearY(float s, float t)
{
	Identity();
	m21 = s;
	m23 = t;
}


void chMatrix::SetShearZ(float s, float t)
{
	Identity();
	m31 = s;
	m32 = t;
}


void chMatrix::SetProjection(const chVector3 *n)
{
	assert(fabs(chVec3DotProduct(n,n) -1.0f) < 0.01f);

	m11 = 1.0f - n->x*n->x;
	m22 = 1.0f - n->y*n->y;
	m33 = 1.0f - n->z*n->z;
	m12 = m21 = -n->x*n->y;
	m13 = m31 = -n->x*n->z;
	m23 = m32 = -n->y*n->z;

	this->ZeroTransalation();

}


void chMatrix::SetReflectionX()
{
	Identity();
	m11 = -1.0f;
}

void chMatrix::SetReflectionY()
{
	Identity();
	m22=-1.0f;
}

void chMatrix::SetReflectionZ()
{
	Identity();
	m33 = -1.0f;
}

void chMatrix::SetReflectionAxis(const chVector3 *axis)
{
	assert(fabs(chVec3DotProduct(axis,axis) - 1.0f) < .01f);

	float a = - 2.0f;
	float ax = a * axis->x;
	float ay = a * axis->y;
	float az = a * axis->z;

	m11 = ax*axis->x + 1.0f;
	m22 = ay*axis->y + 1.0f;
	m32 = az*axis->z + 1.0f;
	m12 = m21 = ax*axis->y;
	m13 = m31 = ax*axis->z;
	m23 = m32 = ay*axis->z;

	ZeroTransalation();
}


float chMatrix::GetDeterminant() const
{
	return	m11 * (m22*m33 - m23*m32)
	+ m12 * (m23*m31 - m21*m33)
	+ m13 * (m21*m32 - m22*m31);
}


void chMatrix::GetTranslation(chVector3 *vec) const
{
	//SAFE_DELETE(vec);
	//vec = new chVector3();

	vec->x = m41;
	vec->y = m42;
	vec->z = m43;
}


void chMatrix::Inverse(chMatrix *mat) const
{
	float d = this->GetDeterminant();

	assert(fabs(d) > 0.000001f);

	float oneoverd = 1.0f/d;

	//SAFE_DELETE(mat);
	//mat = new chMatrix();

	mat->m11 = (m22*m33 - m23*m32) * oneoverd;
	mat->m12 = (m13*m32 - m12*m33) * oneoverd;
	mat->m13 = (m12*m23 - m13*m22) * oneoverd;
	mat->m21 = (m23*m31 - m21*m33) * oneoverd;
	mat->m22 = (m11*m33 - m13*m31) * oneoverd;
	mat->m23 = (m13*m21 - m11*m23) * oneoverd;
	mat->m31 = (m21*m32 - m22*m31) * oneoverd;
	mat->m32 = (m12*m31 - m11*m32) * oneoverd;
	mat->m33 = (m11*m22 - m12*m21) * oneoverd;

	mat->m41 = -(m41*mat->m11 + m42*mat->m21 + m43*mat->m31);
	mat->m42 = -(m41*mat->m12 + m42*mat->m22 + m43*mat->m32);
	mat->m43 = -(m41*mat->m13 + m42*mat->m23 + m43*mat->m33);

}


void chMatrix::GetPosLW(chVector3 *vec) const
{
	this->GetTranslation(vec);
}


void chMatrix::GetPosWL(chVector3 *vec) const
{	
//SAFE_DELETE(vec);
//	vec = new chVector3();
	vec->x = -(m41*m11 + m42*m21 + m43*m31);
	vec->y = -(m41*m12 + m42*m22 + m43*m32);
	vec->z = -(m41*m13 + m42*m23 + m43*m33);
}


chMatrix chMatrix::operator *(const chMatrix &mat) const
{
	chMatrix res;

	//res.ZeroTransalation();

	res.m11 = m11*mat.m11 + m12*mat.m21 + m13*mat.m31;
	res.m12 = m11*mat.m12 + m12*mat.m22 + m13*mat.m32;
	res.m13 = m11*mat.m13 + m12*mat.m23 + m13*mat.m33;

	res.m21 = m21*mat.m11 + m22*mat.m21 + m23*mat.m31;
	res.m22 = m21*mat.m12 + m22*mat.m22 + m23*mat.m32;
	res.m23 = m21*mat.m13 + m22*mat.m23 + m23*mat.m33;

	res.m31 = m31*mat.m11 + m32*mat.m21 + m33*mat.m31;
	res.m32 = m31*mat.m12 + m32*mat.m22 + m33*mat.m32;
	res.m33 = m31*mat.m13 + m32*mat.m23 + m33*mat.m33;

	// Compute the translation portion
	res.m41 = m41*mat.m11 + m42*mat.m21 + m43*mat.m31 + mat.m41;
	res.m42 = m41*mat.m12 + m42*mat.m22 + m43*mat.m32 + mat.m42;
	res.m43 = m41*mat.m13 + m42*mat.m23 + m43*mat.m33 + mat.m43;

	res.m14 = m11*mat.m14 + m12*mat.m24 + m13*mat.m34 + m14*mat.m44;
	res.m24 = m21*mat.m14 + m22*mat.m24 + m23*mat.m34 + m24*mat.m44;
	res.m34 = m31*mat.m14 + m32*mat.m24 + m33*mat.m34 + m34*mat.m44;
	res.m44 = m41*mat.m14 + m42*mat.m24 + m43*mat.m34 + m44*mat.m44;

	//res.m14 = m11*mat.m14 + m12*mat.m24 + m13*mat.m34;
	//res.m24 = m21*mat.m14 + m22*mat.m24 + m23*mat.m34;
	//res.m34 = m31*mat.m14 + m32*mat.m24 + m33*mat.m34;
	//res.m44 = m41*mat.m14 + m42*mat.m24 + m43*mat.m34;

	return res;

}


chMatrix& chMatrix::operator *=(const chMatrix &mat)
{
	return *this=(*this)* mat;
}

///////global functions


chVector3 operator*(const chVector3 &vec,const chMatrix &mat)
{
	chVector3 v(vec.x*mat.m11 + vec.y*mat.m21 + vec.z*mat.m31 + mat.m41,
		vec.x*mat.m12 + vec.y*mat.m22 + vec.z*mat.m32 + mat.m42,
		vec.x*mat.m13 + vec.y*mat.m23 + vec.z*mat.m33 + mat.m43);
	float w = vec.x*mat.m14 + vec.y*mat.m24 + vec.z*mat.m34 + mat.m44;
	
	if(w<CH_EPSILON)
	{
		w=1.0f;
		//assert(false);
	}

	v.x/=w;
	v.y/=w;
	v.z/=w;

	return v;

}

chVector3 chProjectionTransform(const chVector3 &vec,const chMatrix &mat)
{
	chVector3 v(vec.x*mat.m11 + vec.y*mat.m21 + vec.z*mat.m31 + mat.m41,
		vec.x*mat.m12 + vec.y*mat.m22 + vec.z*mat.m32 + mat.m42,
		vec.x*mat.m13 + vec.y*mat.m23 + vec.z*mat.m33 + mat.m43);

	v.x/=v.z;
	v.y/=v.z;
	v.z/=v.z;

//vec = v;

	return v;

}

chVector3& operator*=(chVector3& vec,const chMatrix& mat)
{
	vec = vec * mat;
	return vec;
}


void chMatrix::MakeViewMatrix(const chVector3* position,const chVector3* look,const chVector3* up,const chVector3* right)
{
	ZeroTransalation();

	m11 = right->x;
	m21 = right->y;
	m31 = right->z;
	m41 = -(chVec3DotProduct(position,right));

	m12 = up->x;
	m22 = up->y;
	m32 = up->z;
	m42 = -(chVec3DotProduct(position,up));

	m13 = look->x;
	m23 = look->y;
	m33 = look->z;
	m43 = -(chVec3DotProduct(position,look));

}


void chMatrix::MakeProjectionMatrix(const float fov, const float aspectRatio)
{
	m11=m22=m33=m34=1.0f;
	m12=m13=m14=m21=m23=m24=m31=m32=m44=m41=m42=m43=0.0f;
	float t = 1.0f/tan(fov/2.0f); 
	m11 = t/aspectRatio;
	m22 = t;
}

//
//chMatrix& chMatrix::operator=(const chMatrix& mat)
//{
//	m11=mat.m11;
//	m12=mat.m12;
//	m13=mat.m13;
//	m14=mat.m14;
//
//	m21=mat.m21;
//	m22=mat.m22;
//	m23=mat.m23;
//	m24=mat.m24;
//	
//	m31=mat.m31;
//	m32=mat.m32;
//	m33=mat.m33;
//	m34=mat.m34;
//	
//	m41=mat.m41;
//	m42=mat.m42;
//	m43=mat.m43;
//	m44=mat.m44;
//
//	return *this;
//}
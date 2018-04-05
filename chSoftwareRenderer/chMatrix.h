#pragma once

class chEulerAngles;
class chQuaternion;
class chVector3;

typedef class chMatrix
{
public:

	float m11,m12,m13,m14;
	float m21,m22,m23,m24;
	float m31,m32,m33,m34;
	float m41,m42,m43,m44;

	void Identity();

	//rotation matrix code

	void SetRotationEulerAnglesLW(const chEulerAngles *eAngle);
	void SetRotationEulerAnglesWL(const chEulerAngles *eAngle);

	void SetRotationQuaternion(const chQuaternion* q);

	void SetRotationX(float angle);
	void SetRotationY(float angle);
	void SetRotationZ(float angle);
	void SetRotationAxis(const chVector3 *axis,float angle);

	//translations

	void ZeroTransalation();
	void SetTranslation(const chVector3* vec);
	void SetTranslation(float x,float y,float z);


	//scallng

	void SetScale(const chVector3* scale);
	void SetScaleAlongAxis(const chVector3* axis,float scale);

	//shear

	void SetShearX(float s,float t);
	void SetShearY(float s,float t);
	void SetShearZ(float s,float t);

	//projection

	//projection on plane passing through origin
	void SetProjection(const chVector3 *n);

	//Reflection
	void SetReflectionX();
	void SetReflectionY();
	void SetReflectionZ();

	void SetReflectionAxis(const chVector3 *axis);

	float GetDeterminant() const;

	void GetTranslation(chVector3 *vec) const;

	void GetPosWL(chVector3 *vec) const;
	void GetPosLW(chVector3 *vec) const;

	void Inverse(chMatrix *mat) const;

	chMatrix operator* (const chMatrix& mat) const;
	chMatrix& operator*= (const chMatrix& mat);
	//chMatrix& operator=(const chMatrix& mat);

	void MakeViewMatrix(const chVector3* position,const chVector3* look,const chVector3* up,const chVector3* right);

	void MakeProjectionMatrix(const float fov,const float aspectRatio);


}chMatrix,*LPChMatrix;


extern chVector3 operator*(const chVector3 &vec,const chMatrix &mat);
extern chVector3& operator*=(chVector3 &vec,const chMatrix &mat);


extern chVector3 chProjectionTransform(const chVector3 &vec,const chMatrix &mat);
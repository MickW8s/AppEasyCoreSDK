
#ifndef __CZ_MATRIXAFFINE2D_H__
#define __CZ_MATRIXAFFINE2D_H__

#include "CzVec2.h"

class CzMatrixAffine2d
{
private:
public:
	float		m[3][2];
private:
public:
	CzMatrixAffine2d();
	CzMatrixAffine2d(CzMatrixAffine2d* m0);

	void		Clear();
	void		Copy(CzMatrixAffine2d* m0);
	float		Determinant();
// 	void		Inverse();
	bool		Invert();
	bool		InverseTransform( float x, float y, CzVec2* ov );
// 	void		Transpose();
	void		Identity();
	void		Translate(float x, float y);
	void		Translate(CzVec2* pV);
// 	void		Translate(CzVec3* pV);
	void		TranslateSet(float x, float y);
	void		TranslateSet(CzVec2* pV);
	void		Scale(float x, float y);
// 	void		Scale(CzVec2 *v);
// 	void		Scale(CzVec3 *v);
// 	void		ScaleRotation(float x, float y);
	void		Rotate(float angle);
	void		Multiply(CzMatrixAffine2d* m0);
	void		MultiplyPost(CzMatrixAffine2d* m0);
	void		Multiply(CzMatrixAffine2d* m0, CzMatrixAffine2d* m1);
	void		Transform(float x, float y, CzVec2* ov);
// 	void		TransformSVec(float x, float y, CzSVec2* ov);
	void		Transform(CzVec2* iv, CzVec2* ov);
// 	CzVec2		Transform(CzVec2* iv);
	CzVec2		Transform(float x, float y);
// 	CzSVec2		TransformSVec(CzVec2* iv);
// 	CzSVec2		TransformSVec(float x, float y);
// 	void		TransformRotationOnly(float x, float y, CzVec2 *ov);
// 	void		TransformRotationOnly(CzVec2* iv, CzVec2* ov);
	void		TransformN(CzVec2* iv, CzVec2* ov, int nCount);
// 	void		TransformN(CzVec3* iv, CzVec3* ov, int nCount);
// 	void		TransformNRotationOnly(CzVec2* iv, CzVec2* ov, int nCount);
// 	void		TransformNPreTranslate(CzVec2* iv, CzVec2* ov, int nCount);
// 	float		TransformZ(float x, float y);
// 	float		TransformZRS(float x, float y);
// 
// 	CzVec2		getTranslation();
	float		getX() const;
	float		getY() const;

};

#endif	// __CZ_MATRIXAFFINE2D_H__

#include "CzMatrixAffine2d.h"

#include <string.h>

#include "CzMath.h"

#define CZA0	0
#define CZA1	1
#define CZA2	2
#define CZA3	0
#define CZA4	1
#define CZA5	2

#define CZB0	0
#define CZB1	0
#define CZB2	0
#define CZB3	1
#define CZB4	1
#define CZB5	1


void CzMatrixAffine2d::Clear()
{
	memset(&m, 0, sizeof(m));
	m[CZA0][CZB0] = 1.0f;
	m[CZA4][CZB4] = 1.0f;
}

void CzMatrixAffine2d::Copy(CzMatrixAffine2d* m0)
{
	memcpy(&m, &m0->m, sizeof(m));
}

float CzMatrixAffine2d::Determinant()
{
	return ( ( m[0][0] * m[1][1] ) - ( m[1][0] * m[0][1] ) );
}

bool CzMatrixAffine2d::Invert()
{
	const float det = Determinant();
	if ( det == 0.0f )
	{
		return false;
	}
	const float invDet = 1.0f / det;

	const float t0_0 = m[1][1] * invDet;
	m[1][1] = m[0][0] * invDet;
	m[0][1] = -m[0][1] * invDet;
	m[1][0] = -m[1][0] * invDet;

	const float t2_0 = ( -m[2][0] * t0_0 ) - ( m[2][1] * m[1][0] );
	m[2][1] = ( -m[2][0] * m[0][1] ) - ( m[2][1] * m[1][1] );
	m[0][0] = t0_0;
	m[2][0] = t2_0;

	return true;
}

bool CzMatrixAffine2d::InverseTransform( float x, float y, CzVec2* ov )
{
	const float det = Determinant();
	if ( det == 0.0f )
	{
		ov->x = 0.0f;
		ov->y = 0.0f;
		return false;
	}

	const float invDet = 1.0f / det;
	const float a = ( x - m[2][0] ) * invDet;
	const float b = ( y - m[2][1] ) * invDet;
	ov->x = ( a * m[1][1] ) - ( b * m[1][0] );
	ov->y = ( b * m[0][0] ) - ( a * m[0][1] );

	return true;
}


void CzMatrixAffine2d::Identity()
{
	Clear();
	m[CZA0][CZB0] = 1.0f;
	m[CZA4][CZB4] = 1.0f;
}

void CzMatrixAffine2d::Translate(float x, float y)
{
	Clear();
	m[CZA0][CZB0] = 1.0f;
	m[CZA4][CZB4] = 1.0f;
	m[CZA2][CZB2] = x;
	m[CZA5][CZB5] = y;
}

void CzMatrixAffine2d::Translate(CzVec2* v)
{
	Translate(v->x, v->y);
}

void CzMatrixAffine2d::TranslateSet(float x, float y)
{
	m[CZA2][CZB2] = x;
	m[CZA5][CZB5] = y;
}

void CzMatrixAffine2d::TranslateSet(CzVec2* v)
{
	m[CZA2][CZB2] = v->x;
	m[CZA5][CZB5] = v->y;
}

void CzMatrixAffine2d::Scale(float x, float y)
{
	Clear();
	m[CZA0][CZB0] = x;
	m[CZA4][CZB4] = y;
}

void CzMatrixAffine2d::Rotate(float angle)
{
	angle = CzMath::DegToRad(angle);
	float c = CzMath::cos(angle);
	float s = CzMath::sin(angle);

	Clear();
	m[CZA0][CZB0] = c;
	m[CZA1][CZB1] = -s;
	m[CZA3][CZB3] = s;
	m[CZA4][CZB4] = c;
}

void CzMatrixAffine2d::Multiply(CzMatrixAffine2d* m0)
{
	Multiply(this, m0);
}

void CzMatrixAffine2d::MultiplyPost(CzMatrixAffine2d* m0)
{
	Multiply(m0, this);
}

void CzMatrixAffine2d::Multiply(CzMatrixAffine2d* m0, CzMatrixAffine2d* m1)
{
	float 	m0_0, m0_1, m0_2;
	float 	m00, m01, m02;
	float 	m10, m11, m12;

	m00 = m1->m[CZA0][CZB0];
	m10 = m1->m[CZA3][CZB3];
	m01 = m1->m[CZA1][CZB1];
	m11 = m1->m[CZA4][CZB4];
	m02 = m1->m[CZA2][CZB2];
	m12 = m1->m[CZA5][CZB5];

	m0_0 = m0->m[CZA0][CZB0];
	m0_1 = m0->m[CZA1][CZB1];
	m0_2 = m0->m[CZA2][CZB2];
	m[CZA0][CZB0] = ((m0_0 * m00) + (m0_1 * m10));
	m[CZA1][CZB1] = ((m0_0 * m01) + (m0_1 * m11));
	m[CZA2][CZB2] = ((m0_0 * m02) + (m0_1 * m12) + m0_2);

	m0_0 = m0->m[CZA3][CZB3];
	m0_1 = m0->m[CZA4][CZB4];
	m0_2 = m0->m[CZA5][CZB5];
	m[CZA3][CZB3] = ((m0_0 * m00) + (m0_1 * m10));
	m[CZA4][CZB4] = ((m0_0 * m01) + (m0_1 * m11));
	m[CZA5][CZB5] = ((m0_0 * m02) + (m0_1 * m12) + m0_2);
}

void CzMatrixAffine2d::Transform(float x, float y, CzVec2* ov)
{
	ov->x = (x * m[CZA0][CZB0]) + (y * m[CZA1][CZB1]) + m[CZA2][CZB2];
	ov->y = (x * m[CZA3][CZB3]) + (y * m[CZA4][CZB4]) + m[CZA5][CZB5];
}

void CzMatrixAffine2d::Transform(CzVec2* iv, CzVec2* ov)
{
	Transform(iv->x, iv->y, ov);
}

CzVec2 CzMatrixAffine2d::Transform(float x, float y)
{
	CzVec2 ov;
	Transform(x, y, &ov);
	return ov;
}

void CzMatrixAffine2d::TransformN(CzVec2* iv, CzVec2* ov, int nCount)
{
	float	m00 = m[CZA0][CZB0];
	float	m01 = m[CZA1][CZB1];
	float	m10 = m[CZA3][CZB3];
	float	m11 = m[CZA4][CZB4];
	float	tx = m[CZA2][CZB2];
	float	ty = m[CZA5][CZB5];

	while (nCount-- != 0)
	{
		float x = iv->x;
		float y = iv->y;

		ov->x = (x * m00) + (y * m01) + tx;
		ov->y = (x * m10) + (y * m11) + ty;

		iv++;
		ov++;
	}
}

float CzMatrixAffine2d::getX() const
{
	return m[CZA2][CZB2];
}

float CzMatrixAffine2d::getY() const
{
	return m[CZA5][CZB5];
}

CzMatrixAffine2d::CzMatrixAffine2d()
{
	Clear();
}	

CzMatrixAffine2d::CzMatrixAffine2d( CzMatrixAffine2d* m0 )
{
	Copy( m0 );
}


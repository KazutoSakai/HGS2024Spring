//*********************************************
//
// êîäw(math.h)
// Author : Junichi Uchiyama
//
//*********************************************

#ifndef _ORIGINMATH_H_
#define _ORIGINMATH_H_

#include "main.h"

#define MATH_PI	(3.1415926535f)

float CalcDegreeToRad(float degree);
float CalcRadToDegree(float rad);
bool CalcLerp(const D3DXVECTOR3& target, const D3DXVECTOR3& pos, float time, float maxframe, D3DXVECTOR3* out);
bool CalcLerp(float end, float start, float time, float maxframe, float* out);

#endif
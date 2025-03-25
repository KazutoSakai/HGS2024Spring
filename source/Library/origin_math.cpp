//*********************************************
//
// ”Šw(origin_math.cpp)
// Author : Junichi Uchiyama
//
//*********************************************

#include "origin_math.h"

//------------------------------------
// ƒ‰ƒWƒAƒ“•ÏŠ·
//------------------------------------
float CalcDegreeToRad(float degree)
{
	return degree * (MATH_PI / 180.0f);
}

float CalcRadToDegree(float rad)
{
	return rad * 180.0f / MATH_PI;
}

//------------------------------------
// •âŠÔ
//------------------------------------
bool CalcLerp(const D3DXVECTOR3& target, const D3DXVECTOR3& pos, float time, float maxframe, D3DXVECTOR3* out)
{
	assert(maxframe >= FLT_EPSILON);

	float rate = time / maxframe;
	if (rate > 1.0f) {
		rate = 1.0f;
	}
	D3DXVECTOR3 vec = D3DXVECTOR3(target.x - pos.x, target.y - pos.y, target.z - pos.z);
	*out = pos + vec * rate;
	//time += GetDeltaTime();
	return (rate >= 1.0f);
}

bool CalcLerp(float end, float start, float time, float maxframe, float* out)
{
	assert(maxframe >= FLT_EPSILON);

	float rate = time / maxframe;
	if (rate > 1.0f) {
		rate = 1.0f;
	}
	*out = start + (end - start) * rate;
	//time += GetDeltaTime();
	return (rate >= 1.0f);
}
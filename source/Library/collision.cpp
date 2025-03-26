//*********************************************
//
// �����蔻��(collision.cpp)
// Author : Junichi Uchiyama
//
//*********************************************

#include "collision.h"
#include <algorithm> // std::max, std::min

//------------------------------------
// ��ʊO����
//------------------------------------
bool CollisionOutDisplay(D3DXVECTOR3 pos, float w, float h)
{
	if (pos.y + h <= 0 ||					// ��
		pos.y - h >= SCREEN_HEIGHT ||		// ��
		pos.x + w <= 0 ||					// ��
		pos.x - w >= SCREEN_WIDTH)			// �E
	{
		return true;
	}

	return false;
}

//------------------------------------
// �l�p�`�~�l�p�`
//------------------------------------
bool CollisionSqVsSq(CollisionSquare &sq1, CollisionSquare &sq2, COLLISION_CHECK check)
{
	return false;
}

//------------------------------------
// �l�p�`�~�_
//------------------------------------
bool CollisionSqVsPoint(CollisionSquare &sq, D3DXVECTOR2 &point)
{
	float halfW = sq.w / 2.0f;
	float halfH = sq.h / 2.0f;

	// �l�p�`���ɓ_�����݂��Ă��邩
	if (point.x >= sq.cx - halfW &&		// ���[
		point.x <= sq.cx + halfW &&		// �E�[
		point.y >= sq.cy - halfH &&		// ��[
		point.y <= sq.cy + halfH)		// ���[
	{
		return true;
	}

	return false;
}



//------------------------------------
// �l�p�`(��])�~�_
//------------------------------------
bool CollisionSqRotVsPoint(CollisionSquare& sq, D3DXVECTOR2 &point)
{
	//// ���_���W�̎Z�o
	//D3DXVECTOR2 pVtx[VERTEX_NUM];

	//float w = sq.w / 2, h = sq.h / 2;
	//float length = sqrtf(w * w + h * h);
	//float angle = atan2f(w, h);

	//pVtx[0].x = sq.cx + sinf(sq.radian + MATH_PI + angle) * length;
	//pVtx[0].y = sq.cy + cosf(sq.radian + MATH_PI + angle) * length;

	//pVtx[1].x = sq.cx + sinf(sq.radian + MATH_PI - angle) * length;
	//pVtx[1].y = sq.cy + cosf(sq.radian + MATH_PI - angle) * length;

	//pVtx[2].x = sq.cx + sinf(sq.radian + 0 - angle) * length;
	//pVtx[2].y = sq.cy + cosf(sq.radian + 0 - angle) * length;

	//pVtx[3].x = sq.cx + sinf(sq.radian + 0 + angle) * length;
	//pVtx[3].y = sq.cy + cosf(sq.radian + 0 + angle) * length;

	//// �e���_�ɂ��Ď��v���Ńx�N�g���쐬
	//D3DXVECTOR2 vec[VERTEX_NUM];
	//vec[0].x = pVtx[1].x - pVtx[0].x;
	//vec[1].x = pVtx[3].x - pVtx[1].x;
	//vec[2].x = pVtx[2].x - pVtx[3].x;
	//vec[3].x = pVtx[0].x - pVtx[2].x;

	//vec[0].y = pVtx[1].y - pVtx[0].y;
	//vec[1].y = pVtx[3].y - pVtx[1].y;
	//vec[2].y = pVtx[2].y - pVtx[3].y;
	//vec[3].y = pVtx[0].y - pVtx[2].y;

	//// �ӂ̎n�_����point�ւ̃x�N�g���쐬
	//D3DXVECTOR2 vecP[VERTEX_NUM];
	//vecP[0] = point - pVtx[0];
	//vecP[1] = point - pVtx[1];
	//vecP[2] = point - pVtx[3];
	//vecP[3] = point - pVtx[2];

	//// �Q�̃x�N�g���̊O�ό��ʂŔ���
	//float cross = 0;
	//for (int i = 0; i < VERTEX_NUM; i++)
	//{
	//	D3DXVec2Normalize(&vecP[i], &vecP[i]);
	//	cross = vec[i].x * vecP[i].y - vecP[i].x * vec[i].y;

	//	if (cross < 0) 
	//	{
	//		// �ЂƂł��͈͊O�̂��̂�����Γ������Ă��Ȃ�
	//		return false;
	//	}
	//}

	return true;
}


bool CollisionSqVsCircleReflection(CollisionSquare& sq, CollisionCircle& c, D3DXVECTOR2* move)
{
	// 1. ��`�̈���́g�ł��~�̒��S�ɋ߂��_�h�����߂�
	float rx = sq.cx - sq.w / 2.0f;
	float ry = sq.cy - sq.h / 2.0f;

	float closestX = max(rx, min(c.cx, rx + sq.w));
	float closestY = max(ry, min(c.cy, ry + sq.h));

	// 2. ���̓_(closestX, closestY) �Ɖ~�̒��S(cx, cy) �Ƃ̋������v�Z
	float dx = c.cx - closestX;
	float dy = c.cy - closestY;

	// 3. �������~�̔��a�ȉ��Ȃ�Փ�
	//    �i�������v�Z����������Ȃ� (dx*dx + dy*dy) <= (r*r) �ł��悢�j
	float distanceSquared = dx * dx + dy * dy;
	float rSquared = c.r * c.r;

	if (distanceSquared <= rSquared)
	{
		// 4. �@���x�N�g�� n �����߂� (��` -> �~���S)
		D3DXVECTOR2 n = { dx, dy };
		D3DXVec2Normalize(&n, &n);

		// 5. ���x�x�N�g���𔽎�
		D3DXVECTOR2 v = { move->x, move->y };
		float d = v.x * n.x + v.y * n.y;
		D3DXVECTOR2 vr = D3DXVECTOR2(v.x - 2.0f * d * n.x, v.y - 2.0f * d * n.y);  // ���˃x�N�g��

		move->x = vr.x;
		move->y = vr.y;

		return true;
	}

	return false;
}
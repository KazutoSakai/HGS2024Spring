//*********************************************
//
// 当たり判定(collision.cpp)
// Author : Junichi Uchiyama
//
//*********************************************

#include "collision.h"
#include <algorithm> // std::max, std::min

//------------------------------------
// 画面外判定
//------------------------------------
bool CollisionOutDisplay(D3DXVECTOR3 pos, float w, float h)
{
	if (pos.y + h <= 0 ||					// 上
		pos.y - h >= SCREEN_HEIGHT ||		// 下
		pos.x + w <= 0 ||					// 左
		pos.x - w >= SCREEN_WIDTH)			// 右
	{
		return true;
	}

	return false;
}

//------------------------------------
// 四角形×四角形
//------------------------------------
bool CollisionSqVsSq(CollisionSquare &sq1, CollisionSquare &sq2, COLLISION_CHECK check)
{
	return false;
}

//------------------------------------
// 四角形×点
//------------------------------------
bool CollisionSqVsPoint(CollisionSquare &sq, D3DXVECTOR2 &point)
{
	float halfW = sq.w / 2.0f;
	float halfH = sq.h / 2.0f;

	// 四角形内に点が存在しているか
	if (point.x >= sq.cx - halfW &&		// 左端
		point.x <= sq.cx + halfW &&		// 右端
		point.y >= sq.cy - halfH &&		// 上端
		point.y <= sq.cy + halfH)		// 下端
	{
		return true;
	}

	return false;
}



//------------------------------------
// 四角形(回転)×点
//------------------------------------
bool CollisionSqRotVsPoint(CollisionSquare& sq, D3DXVECTOR2 &point)
{
	//// 頂点座標の算出
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

	//// 各頂点について時計回りでベクトル作成
	//D3DXVECTOR2 vec[VERTEX_NUM];
	//vec[0].x = pVtx[1].x - pVtx[0].x;
	//vec[1].x = pVtx[3].x - pVtx[1].x;
	//vec[2].x = pVtx[2].x - pVtx[3].x;
	//vec[3].x = pVtx[0].x - pVtx[2].x;

	//vec[0].y = pVtx[1].y - pVtx[0].y;
	//vec[1].y = pVtx[3].y - pVtx[1].y;
	//vec[2].y = pVtx[2].y - pVtx[3].y;
	//vec[3].y = pVtx[0].y - pVtx[2].y;

	//// 辺の始点からpointへのベクトル作成
	//D3DXVECTOR2 vecP[VERTEX_NUM];
	//vecP[0] = point - pVtx[0];
	//vecP[1] = point - pVtx[1];
	//vecP[2] = point - pVtx[3];
	//vecP[3] = point - pVtx[2];

	//// ２つのベクトルの外積結果で判定
	//float cross = 0;
	//for (int i = 0; i < VERTEX_NUM; i++)
	//{
	//	D3DXVec2Normalize(&vecP[i], &vecP[i]);
	//	cross = vec[i].x * vecP[i].y - vecP[i].x * vec[i].y;

	//	if (cross < 0) 
	//	{
	//		// ひとつでも範囲外のものがあれば当たっていない
	//		return false;
	//	}
	//}

	return true;
}


bool CollisionSqVsCircleReflection(CollisionSquare& sq, CollisionCircle& c, D3DXVECTOR2* move)
{
	// 1. 矩形領域内の“最も円の中心に近い点”を求める
	float rx = sq.cx - sq.w / 2.0f;
	float ry = sq.cy - sq.h / 2.0f;

	float closestX = max(rx, min(c.cx, rx + sq.w));
	float closestY = max(ry, min(c.cy, ry + sq.h));

	// 2. その点(closestX, closestY) と円の中心(cx, cy) との距離を計算
	float dx = c.cx - closestX;
	float dy = c.cy - closestY;

	// 3. 距離が円の半径以下なら衝突
	//    （平方根計算を避けたいなら (dx*dx + dy*dy) <= (r*r) でもよい）
	float distanceSquared = dx * dx + dy * dy;
	float rSquared = c.r * c.r;

	if (distanceSquared <= rSquared)
	{
		// 4. 法線ベクトル n を求める (矩形 -> 円中心)
		D3DXVECTOR2 n = { dx, dy };
		D3DXVec2Normalize(&n, &n);

		// 5. 速度ベクトルを反射
		D3DXVECTOR2 v = { move->x, move->y };
		float d = v.x * n.x + v.y * n.y;
		D3DXVECTOR2 vr = D3DXVECTOR2(v.x - 2.0f * d * n.x, v.y - 2.0f * d * n.y);  // 反射ベクトル

		move->x = vr.x;
		move->y = vr.y;

		return true;
	}

	return false;
}
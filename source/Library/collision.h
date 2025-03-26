//*********************************************
//
// 当たり判定(collision.h)
// Author : Junichi Uchiyama
//
//*********************************************

#pragma once
#ifndef COLLISION_H_
#define COLLISION_H_

#include "main.h"

//---------------------
// 列挙

// ヒット判定の種類
enum COLLISION_CHECK
{
	COLCHECK_ALL,		// 全て含まれているか
	COLCHECK_HIT,		// 衝突したか

	COLCHECK_MAX
};

//---------------------
// 構造体

// 四角形情報
struct CollisionSquare
{
	float cx, cy;		// 中心座標
	float w, h;			// 横縦幅
	float radian;		// 回転度数
};

// 円
struct CollisionCircle
{
	float cx, cy;		// 中心座標
	float r;			// 半径
};

// 画面外判定
// pos：中心座標
// w：横サイズ
// h：縦サイズ
// return：true == hit
bool CollisionOutDisplay(D3DXVECTOR3 pos, float w, float h);

// 四角形×四角形
// sq1：四角形１
// sq2：四角形２
// check：判定方法
// return：true == hit
bool CollisionSqVsSq(CollisionSquare &sq1, CollisionSquare &sq2, COLLISION_CHECK check);

// 四角形×点
// sq：四角形
// point：点
// return：true == hit
bool CollisionSqVsPoint(CollisionSquare &sq, D3DXVECTOR2 &point);

// 四角形(回転)×点
// sq：四角形(radianを指定)
// point：点
// return：true == hit
bool CollisionSqRotVsPoint(CollisionSquare& sq, D3DXVECTOR2 &point);

/// <summary>
/// 
/// </summary>
/// <param name="sq"></param>
/// <param name="c"></param>
/// <returns></returns>
bool CollisionSqVsCircleReflection(CollisionSquare& sq, CollisionCircle& c, D3DXVECTOR2* move);

#endif
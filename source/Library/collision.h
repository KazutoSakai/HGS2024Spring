//*********************************************
//
// �����蔻��(collision.h)
// Author : Junichi Uchiyama
//
//*********************************************

#pragma once
#ifndef COLLISION_H_
#define COLLISION_H_

#include "main.h"

//---------------------
// ��

// �q�b�g����̎��
enum COLLISION_CHECK
{
	COLCHECK_ALL,		// �S�Ċ܂܂�Ă��邩
	COLCHECK_HIT,		// �Փ˂�����

	COLCHECK_MAX
};

//---------------------
// �\����

// �l�p�`���
struct CollisionSquare
{
	float cx, cy;		// ���S���W
	float w, h;			// ���c��
	float radian;		// ��]�x��
};

// �~
struct CollisionCircle
{
	float cx, cy;		// ���S���W
	float r;			// ���a
};

// ��ʊO����
// pos�F���S���W
// w�F���T�C�Y
// h�F�c�T�C�Y
// return�Ftrue == hit
bool CollisionOutDisplay(D3DXVECTOR3 pos, float w, float h);

// �l�p�`�~�l�p�`
// sq1�F�l�p�`�P
// sq2�F�l�p�`�Q
// check�F������@
// return�Ftrue == hit
bool CollisionSqVsSq(CollisionSquare &sq1, CollisionSquare &sq2, COLLISION_CHECK check);

// �l�p�`�~�_
// sq�F�l�p�`
// point�F�_
// return�Ftrue == hit
bool CollisionSqVsPoint(CollisionSquare &sq, D3DXVECTOR2 &point);

// �l�p�`(��])�~�_
// sq�F�l�p�`(radian���w��)
// point�F�_
// return�Ftrue == hit
bool CollisionSqRotVsPoint(CollisionSquare& sq, D3DXVECTOR2 &point);

/// <summary>
/// 
/// </summary>
/// <param name="sq"></param>
/// <param name="c"></param>
/// <returns></returns>
bool CollisionSqVsCircleReflection(CollisionSquare& sq, CollisionCircle& c, D3DXVECTOR2* move);

#endif
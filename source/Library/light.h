//*********************************************
//
// ライト(light.h)
// Author : Junichi Uchiyama
//
//*********************************************

#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "main.h"

/// <summary>
/// ライト
/// </summary>
class CLight
{
private:
	static const int MAX_LIGHT = 2;

public:
	CLight();			// コンストラクタ
	~CLight() {};		// デストラクタ

	HRESULT Init();		// 初期化

private:
	D3DLIGHT9 m_Light[MAX_LIGHT];	// ライト情報
};

#endif
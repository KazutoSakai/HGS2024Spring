//*********************************************
//
// 数字表示(number.h)
// Author : Junichi Uchiyama
//
//*********************************************

#ifndef _NUMBER_H_
#define _NUMBER_H_

#include "object2D.h"

/// <summary>
/// 数字管理
/// </summary>
class CNumber : public CObject2D
{
public:
	CNumber(Priority priority = Priority::UI);		// コンストラクタ
	~CNumber();		// デストラクタ

	HRESULT Init() override;	// 初期化
	void Uninit() override;		// 解放
	void Update() override;		// 更新
	void Draw() override;		// 描画

	static CNumber* Create(const D3DXVECTOR3& pos);		// 生成

	void SetNumber(int num);		// 数字設定

private:

};

#endif
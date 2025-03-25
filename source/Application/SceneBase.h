//*********************************************
//
// シーン基底(SceneBase.h)
// Author : Junichi Uchiyama
//
//*********************************************

#ifndef _SCENEBASE_H_
#define _SCENEBASE_H_

#include "main.h"
#include "view.h"

/// <summary>
/// シーン基底
/// </summary>
class CSceneBase
{
public:
	//---------------------
	// public Method
	CSceneBase() {}					// コンストラクタ
	virtual ~CSceneBase() {}		// デストラクタ

	virtual HRESULT Init() = 0;		// 初期化
	virtual void Uninit() = 0;		// 破棄
	virtual void Update() = 0;		// 更新
	virtual void Draw() = 0;		// 描画

};

#endif
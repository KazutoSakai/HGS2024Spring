//*********************************************
//
// ゲームタイトル(SceneTitle.h)
// Author : Junichi Uchiyama
//
//*********************************************

#ifndef _SCENETITLE_H_
#define _SCENETITLE_H_

#include "main.h"

#include "SceneBase.h"

/// <summary>
/// ゲームタイトル画面管理
/// </summary>
class CSceneTitle : public CSceneBase
{
public:
	//---------------------
	// public Method
	CSceneTitle() {};
	~CSceneTitle() override {};

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

private:


};

#endif
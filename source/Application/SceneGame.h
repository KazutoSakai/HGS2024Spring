//*********************************************
//
// ゲームメイン画面(SceneGame.h)
// Author : Junichi Uchiyama
//
//*********************************************

#ifndef _SCENEGAME_H_
#define _SCENEGAME_H_

#include "main.h"

#include "SceneBase.h"

/// <summary>
/// ゲームメイン画面管理
/// </summary>
class CSceneGame : public CSceneBase
{
public:
	//---------------------
	// public Method
	CSceneGame() {};
	~CSceneGame() override {};

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	//---------------------
	// static Method
	static CSceneGame* Create();

private:


};

#endif
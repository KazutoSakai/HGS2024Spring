//*********************************************
//
// ゲームランキング画面(SceneRanking.h)
// Author : Junichi Uchiyama
//
//*********************************************

#ifndef _SCENERanking_H_
#define _SCENERanking_H_

#include "main.h"

#include "SceneBase.h"

/// <summary>
/// ゲームランキング画面管理
/// </summary>
class CSceneRanking : public CSceneBase
{
public:
	//---------------------
	// public Method
	CSceneRanking() {};
	~CSceneRanking() override {};

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

private:


};

#endif
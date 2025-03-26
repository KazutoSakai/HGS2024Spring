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

class CPlayer;
class CTimer;
class CSideUI;
class CObject2D;

/// <summary>
/// ゲームメイン画面管理
/// </summary>
class CSceneGame : public CSceneBase
{
public:
	//---------------------
	// public Method
	CSceneGame();
	~CSceneGame() override {};

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	//---------------------
	// static Method
	//static CSceneGame* Create();

	void Resporn();
	void GameEnd();
	void RestartGame();

private:

	static const int LIFE_MAX = 3;

	CPlayer* m_pPlayer;

	int m_Life;

	CTimer* m_pTimer;

	CSideUI* m_pSideL;
	CSideUI* m_pSideR;

	CObject2D* m_pDarkPolygon;

};

#endif
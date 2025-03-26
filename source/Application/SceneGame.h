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
class CBall;
class CBestScore;
class CNumber;

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

	void Resporn(bool isSubLife);
	void GameEnd();
	void RestartGame();

	// ゲーム実行中（リザルトは除く）
	bool IsGameRun() { return m_Life > 0; }

private:

	static const int LIFE_MAX = 3;

	enum class GameState
	{
		Wait,
		Game,
		Result,
	};

	GameState m_GameState;

	CPlayer* m_pPlayer;
	CBall* m_pBall;

	int m_Life;

	CTimer* m_pTimer;

	CSideUI* m_pSideL;
	CSideUI* m_pSideR;

	CObject2D* m_pDarkPolygon;

	CBestScore* m_pBestScore;

	CNumber* m_pNumber;
};

#endif
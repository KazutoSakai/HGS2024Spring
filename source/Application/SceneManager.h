//*********************************************
//
// シーンの切替や管理(SceneManager.h)
// Author : Junichi Uchiyama
//
//*********************************************

#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_

#include "SceneBase.h"

class CSceneManager
{
public:
	//---------------------
	// enum

	// シーンの種類（画面が切り替わるもの）
	enum class SceneType
	{
		Title,
		Game,
		Result,
		Ranking,

		Max
	};

	//---------------------
	// default
	CSceneManager();
	~CSceneManager();

	//---------------------
	// Method
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
	void ChangeScene(SceneType sceneType, bool killObjects);

private:
	//---------------------
	// Member
	CSceneBase* m_pScene;		// 現在のインスタンス
	SceneType m_type;			// 現在のシーン

	//---------------------
	// Method
	void ReleaseScene();		// シーンのUninitを呼び出して初期化

};

#endif
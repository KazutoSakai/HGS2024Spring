//*********************************************
//
// シーンの切替や管理(SceneManager.cpp)
// Author : Junichi Uchiyama
//
//*********************************************

#include "SceneManager.h"

#include "SceneTitle.h"
#include "SceneResult.h"
#include "SceneGame.h"
#include "SceneRanking.h"

#include "object.h"

/// <summary>
/// 初期化
/// </summary>
CSceneManager::CSceneManager() : m_pScene(nullptr), 
								m_type(SceneType::Title)
{

}

/// <summary>
/// 解放
/// </summary>
CSceneManager::~CSceneManager()
{
	if (m_pScene != nullptr)
		delete m_pScene;
}

/// <summary>
/// 初期設定
/// </summary>
/// <returns></returns>
HRESULT CSceneManager::Init()
{
	// デフォルトの画面
	SceneType defaultType = SceneType::Game;

	ChangeScene(defaultType, false);

	return S_OK;
}

/// <summary>
/// 解放処理
/// </summary>
void CSceneManager::Uninit()
{
	ReleaseScene();
}

/// <summary>
/// シーンの更新やフェード管理
/// </summary>
void CSceneManager::Update()
{
	// フェード処理
	// TODO:

	if (m_pScene != nullptr)
	{
		m_pScene->Update();
	}
}

/// <summary>
/// シーンの描画処理
/// </summary>
void CSceneManager::Draw()
{
	if (m_pScene != nullptr)
	{
		m_pScene->Draw();
	}
}

/// <summary>
/// シーン変更
/// </summary>
/// <param name="sceneType">遷移先</param>
void CSceneManager::ChangeScene(SceneType sceneType, bool killObjects)
{
	// 後処理
	ReleaseScene();

	// オブジェクトを破棄する
	if (killObjects)
		CObject::ReleaseAll();

	// 指定できるか判定
	switch (sceneType)
	{
	case CSceneManager::SceneType::Title:
		m_pScene = DBG_NEW CSceneTitle();
		break;
	case CSceneManager::SceneType::Game:
		m_pScene = DBG_NEW CSceneGame();
		break;
	case CSceneManager::SceneType::Result:
		m_pScene = DBG_NEW CSceneResult();
		break;
	case CSceneManager::SceneType::Ranking:
		m_pScene = DBG_NEW CSceneRanking();
		break;
	default:
		assert(false && "SceneManager::ChangeScene sceneType is default.");
		break;
	}

	// 初期設定
	if (m_pScene != nullptr)
	{
		m_pScene->Init();
	}
}

/// <summary>
/// シーンのUninitを呼び出して初期化
/// </summary>
void CSceneManager::ReleaseScene()
{
	if (m_pScene != nullptr)
	{
		m_pScene->Uninit();
		delete m_pScene;
		m_pScene = nullptr;
	}
}
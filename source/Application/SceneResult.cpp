//*********************************************
//
// ゲームリザルト画面管理(SceneResult.cpp)
// Author : Junichi Uchiyama
//
//*********************************************

#include "SceneResult.h"
#include "application.h"

#include "object2D.h"
#include "texture.h"

/// <summary>
/// 初期化
/// </summary>
/// <returns></returns>
HRESULT CSceneResult::Init()
{
	//----------------------------
	// サンプルコード

	// ポリゴン生成　※継承でも利用可能。CObjectクラスに登録。
	auto obj = CObject2D::Create();
	// 位置設定。基準点は中心がデフォ。
	obj->SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
	// (x, y) = (横、縦)
	obj->SetSize(D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT));
	// テクスチャ読み込み（解放はCApplication）
	auto pTex = CApplication::GetInstance()->GetTexture();
	int texId = pTex->LoadTexture("data/sample/texture/texture003.jpg");
	// バインド
	obj->BindTexture(pTex->GetTexture(texId));

	return S_OK;
}

/// <summary>
/// 解放
/// </summary>
void CSceneResult::Uninit()
{

}

/// <summary>
/// 更新
/// </summary>
void CSceneResult::Update()
{
	// 決定キー
	if (CApplication::GetInstance()->GetInput()->GetTrigger(CInputManager::InputType::Decide_A))
	{
		CApplication::GetInstance()->GetScene()->ChangeScene(CSceneManager::SceneType::Ranking, true);
	}
}

/// <summary>
/// 描画
/// </summary>
void CSceneResult::Draw()
{

}
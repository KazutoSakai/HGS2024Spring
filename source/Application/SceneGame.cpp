//*********************************************
//
// ゲームメイン画面管理(SceneGame.cpp)
// Author : Junichi Uchiyama
//
//*********************************************

#include "SceneGame.h"
#include "application.h"

#include "object2D.h"
#include "texture.h"
#include "effect.h"

#include "objectX.h"

#include "input.h"

CObject2D* obj2D;
CObjectX* objX;

/// <summary>
/// 初期化
/// </summary>
/// <returns></returns>
HRESULT CSceneGame::Init()
{
	//----------------------------
	// サンプルコード

	// ポリゴン生成　※継承でも利用可能。CObjectクラスに登録。
	obj2D = CObject2D::Create(CObject::Priority::Character);
	// 位置設定。基準点は中心がデフォ。
	obj2D->SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
	// (x, y) = (横、縦)
	obj2D->SetSize(D3DXVECTOR2(100, 100));
	// テクスチャ読み込み（解放はCApplication）
	auto pTex = CApplication::GetInstance()->GetTexture();
	int texId = pTex->LoadTexture("data/sample/texture/player001.png");
	// バインド
	obj2D->BindTexture(pTex->GetTexture(texId));

	// Xファイルモデル生成
	objX = CObjectX::Create(D3DXVECTOR3(0, 0, 0), "data/sample/model/chara/01_head.x");

	return S_OK;
}

/// <summary>
/// 解放
/// </summary>
void CSceneGame::Uninit()
{

}

/// <summary>
/// 更新
/// </summary>
void CSceneGame::Update()
{
	//----------------------------
	// サンプルコード
	auto pInput = CApplication::GetInstance()->GetInput();
	{
		auto pos = obj2D->GetPos();
		if (pInput->GetPress(CInputManager::InputType::Move_Up))
			pos.y -= 2.0f;
		if (pInput->GetPress(CInputManager::InputType::Move_Down))
			pos.y += 2.0f;
		if (pInput->GetPress(CInputManager::InputType::Move_Left))
			pos.x -= 2.0f;
		if (pInput->GetPress(CInputManager::InputType::Move_Right))
			pos.x += 2.0f;
		obj2D->SetPos(pos);

		// エフェクト（コンストラクタで描画順を設定している）
		auto pEffect = CEffect::Create(pos, D3DCOLOR_ARGB(255, 255, 255, 255), 10);
		pEffect->SetSize(D3DXVECTOR2(100.0f, 100.0f));
	}

	{
		auto pos = objX->GetPos();
		if (pInput->GetPress(CInputManager::InputType::Move_Up))
			pos.y += 2.0f;
		if (pInput->GetPress(CInputManager::InputType::Move_Down))
			pos.y -= 2.0f;
		if (pInput->GetPress(CInputManager::InputType::Move_Left))
			pos.x -= 2.0f;
		if (pInput->GetPress(CInputManager::InputType::Move_Right))
			pos.x += 2.0f;
		objX->SetPos(pos);
	}
	

	// 決定キー
	if (CApplication::GetInstance()->GetInput()->GetTrigger(CInputManager::InputType::Decide_A))
	{
		CApplication::GetInstance()->GetScene()->ChangeScene(CSceneManager::SceneType::Result, true);
	}
}

/// <summary>
/// 描画
/// </summary>
void CSceneGame::Draw()
{

}
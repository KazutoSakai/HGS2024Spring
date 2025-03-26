//*********************************************
//
// ゲームメイン画面管理(SceneGame.cpp)
// Author : Junichi Uchiyama
//
//*********************************************

#include "SceneGame.h"
#include "application.h"
#include "input.h"

#include "Player.h"
#include "Ball.h"
#include "Block.h"
#include "BlockManager.h"

/// <summary>
/// 初期化
/// </summary>
/// <returns></returns>
HRESULT CSceneGame::Init()
{
	auto player = CPlayer::Create();

	auto ball = CBall::Create();
	ball->SetPlayerID(player->GetId());
	ball->SetPos(D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0.0f));

	CBlockManager::GetInstance()->Init();

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

}

/// <summary>
/// 描画
/// </summary>
void CSceneGame::Draw()
{

}
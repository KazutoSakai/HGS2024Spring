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

#include "number.h"
#include "ScoreManager.h"

#include "Timer.h"

#include "SideUI.h"

/// <summary>
/// 初期化
/// </summary>
/// <returns></returns>
HRESULT CSceneGame::Init()
{
	auto ball = CBall::Create();
	auto player = CPlayer::Create();

	ball->SetPlayerID(player->GetId());
	ball->SetPos(D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0.0f));

	CBlockManager::GetInstance()->Init();

	// ベストスコア
	{
		float startX = SCREEN_WIDTH - CApplication::SCREEN_SIDE_WIDTH;
		const float startY = 0;
		const float sizeX = 28;
		for (int x = 0; x < 8; x++)
		{
			auto pNum = CNumber::Create(D3DXVECTOR3(startX + x * sizeX, startY, 0));
			pNum->SetPosType(CObject2D::POSTYPE::LeftTop);
			pNum->SetSize(D3DXVECTOR2(sizeX, 56));
			pNum->SetNumber(x);
		}
	}

	// 現在のスコア
	CScoreManager::GetInstance()->Init();

	// 時間
	CTimer::Create();

	// サイドの表示
	CSideUI::Create(true);
	CSideUI::Create(false);

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
	// スコア
	CScoreManager::GetInstance()->Update();

#ifdef _DEBUG
	auto pInput = CApplication::GetInstance()->GetInput();
	if (pInput->GetPress(CInputManager::InputType::Move_Up))
	{
		CScoreManager::GetInstance()->AddScore(1);
	}
#endif
}

/// <summary>
/// 描画
/// </summary>
void CSceneGame::Draw()
{

}
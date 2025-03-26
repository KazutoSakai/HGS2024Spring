//*********************************************
//
// �Q�[�����C����ʊǗ�(SceneGame.cpp)
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

/// <summary>
/// ������
/// </summary>
/// <returns></returns>
HRESULT CSceneGame::Init()
{
	auto player = CPlayer::Create();

	auto ball = CBall::Create();
	ball->SetPlayerID(player->GetId());
	ball->SetPos(D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0.0f));

	CBlockManager::GetInstance()->Init();

	// �x�X�g�X�R�A
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

	// ���݂̃X�R�A
	CScoreManager::GetInstance()->Init();

	return S_OK;
}

/// <summary>
/// ���
/// </summary>
void CSceneGame::Uninit()
{

}

/// <summary>
/// �X�V
/// </summary>
void CSceneGame::Update()
{
	// �X�R�A
	CScoreManager::GetInstance()->Update();

	auto pInput = CApplication::GetInstance()->GetInput();
	if (pInput->GetPress(CInputManager::InputType::Move_Up))
	{
		CScoreManager::GetInstance()->AddScore(1);
	}
}

/// <summary>
/// �`��
/// </summary>
void CSceneGame::Draw()
{

}
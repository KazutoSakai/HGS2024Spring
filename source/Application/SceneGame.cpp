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

#include "Timer.h"

#include "SideUI.h"

#include "RateBallManager.h"

CSceneGame::CSceneGame() : m_pPlayer(nullptr), m_pTimer(nullptr), m_pSideL(nullptr), m_pSideR(nullptr), m_pDarkPolygon(nullptr)
{
	m_Life = 0;
}

/// <summary>
/// ������
/// </summary>
/// <returns></returns>
HRESULT CSceneGame::Init()
{
	auto ball = CBall::Create();
	m_pPlayer = CPlayer::Create();

	ball->SetPlayerID(m_pPlayer->GetId());

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

	// ����
	m_pTimer = CTimer::Create();

	// �T�C�h�̕\��
	m_pSideL = CSideUI::Create(true);
	m_pSideR = CSideUI::Create(false);

	// �c�@
	m_Life = LIFE_MAX;

	// �����Â��|���S��
	if (m_pDarkPolygon == nullptr)
	{
		m_pDarkPolygon = CObject2D::Create(CObject::Priority::UI);
		m_pDarkPolygon->SetSize(D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT));
		m_pDarkPolygon->SetColor(D3DCOLOR_ARGB(128, 0, 0, 0));
		m_pDarkPolygon->SetPosType(CObject2D::POSTYPE::LeftTop);
		m_pDarkPolygon->SetDrawFlg(false);
	}
	else
	{
		m_pDarkPolygon->SetDrawFlg(false);
	}

	// �{������
	CRateBallManager::GetInstance()->Init();

	return S_OK;
}

/// <summary>
/// ���
/// </summary>
void CSceneGame::Uninit()
{
	CBlockManager::GetInstance()->ReleaseBlock();
	CScoreManager::GetInstance()->Uninit();
	CRateBallManager::GetInstance()->Uninit();
}

/// <summary>
/// �X�V
/// </summary>
void CSceneGame::Update()
{
	// �X�R�A
	CScoreManager::GetInstance()->Update();

	// �{������
	CRateBallManager::GetInstance()->Update();

	auto pInput = CApplication::GetInstance()->GetInput();
	// ���U���g
	if (m_Life <= 0)
	{
		if (pInput->GetTrigger(CInputManager::InputType::Decide_A))
		{
			CApplication::GetInstance()->GetScene()->ChangeScene(CSceneManager::SceneType::Game, true);
			return;
		}
	}

#ifdef _DEBUG
	if (pInput->GetPress(CInputManager::InputType::Move_Up))
	{
		CScoreManager::GetInstance()->AddScore(1);
	}
#endif
}

/// <summary>
/// �`��
/// </summary>
void CSceneGame::Draw()
{
	
}

void CSceneGame::Resporn()
{
	// �c�@�����炷
	m_Life--;

	if (m_Life <= 0)
	{
		CScoreManager::GetInstance()->LatestScore();
		GameEnd();
		return;
	}

	// �u���b�N�̍Đ���
	CBlockManager::GetInstance()->ReleaseBlock();
	CBlockManager::GetInstance()->Init();

	auto ball = CBall::Create();
	ball->SetPlayerID(m_pPlayer->GetId());
}

void CSceneGame::GameEnd()
{
	// ���C�t���[���ɂ���
	m_Life = 0;

	// ���Â��|���S��
	if(m_pDarkPolygon != nullptr)
		m_pDarkPolygon->SetDrawFlg(true);

	// ���Ԃ��~�߂�
	if (m_pTimer != nullptr)
	{
		m_pTimer->StopTimer();
	}

	CScoreManager::GetInstance()->ResultScore();
}

void CSceneGame::RestartGame()
{
	// �j���A�㏈��
	if (m_pPlayer != nullptr)
		m_pPlayer->Uninit();
	CBlockManager::GetInstance()->ReleaseBlock();
	CScoreManager::GetInstance()->Uninit();
	CRateBallManager::GetInstance()->Uninit();
	if (m_pTimer != nullptr)
		m_pTimer->Uninit();
	if (m_pSideL != nullptr)
		m_pSideL->Uninit();
	if (m_pSideR != nullptr)
		m_pSideR->Uninit();

	// �����ݒ�
	Init();
}
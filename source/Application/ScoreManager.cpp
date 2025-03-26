
#include "ScoreManager.h"
#include "application.h"

#include "collision.h"


CScoreManager::CScoreManager()
{
	for (int i = 0; i < SCORE_NUM; i++)
		m_pNumberList[i] = nullptr;

	m_score = 0;
	m_destScore = 0;
}

CScoreManager::~CScoreManager()
{

}

HRESULT CScoreManager::Init()
{
	// ���݂̃X�R�A
	float startX = SCREEN_WIDTH - CApplication::SCREEN_SIDE_WIDTH;
	const float startY = 100;
	const float sizeX = 28;

	for (int x = 0; x < SCORE_NUM; x++)
	{
		auto pNum = CNumber::Create(D3DXVECTOR3(startX + x * sizeX, startY, 0));
		pNum->SetPosType(CObject2D::POSTYPE::LeftTop);
		pNum->SetSize(D3DXVECTOR2(sizeX, 56));
		pNum->SetNumber(0);
		m_pNumberList[SCORE_NUM - 1 - x] = pNum;
	}

	m_score = 0;
	m_destScore = 0;

	

	return S_OK;
}

void CScoreManager::Uninit()
{
	for (int x = 0; x < SCORE_NUM; x++)
	{
		m_pNumberList[x]->Uninit();
		m_pNumberList[x] = nullptr;
	}
}

void CScoreManager::Update()
{
	// �ڕW�X�R�A�܂ŉ��Z����
	if (m_score + 1000000 < m_destScore)
	{
		m_score += 111111;
		SetScore(m_score);
	}
	else if (m_score + 100000 < m_destScore)
	{
		m_score += 11111;
		SetScore(m_score);
	}
	else if (m_score + 10000 < m_destScore)
	{
		m_score += 1111;
		SetScore(m_score);
	}
	else if (m_score < m_destScore)
	{
		m_score++;
		SetScore(m_score);
	}

	
}

void CScoreManager::Draw()
{

}

void CScoreManager::AddScore(int score)
{
	m_destScore += score;
}

void CScoreManager::SetScore(int score)
{
	m_score = score;

	// �����̏���
	int tmpScore = m_score;
	for (int i = 0; i < SCORE_NUM; i++)
	{
		auto pNum = m_pNumberList[i];

		int num = 0;

		// 1���ڂ��擾
		num = tmpScore % 10;

		// 1�����炷
		tmpScore /= 10;

		pNum->SetNumber(num);
	}

	// �X�R�A�����̐��l�ɂȂ�ƐF��ς���
	if (m_score > 50000)
	{
		auto pTex = CApplication::GetInstance()->GetTexture();
		int texID = pTex->LoadTexture("data/sample/texture/number003.png");;

		if (m_score > 80000)
		{
			texID = pTex->LoadTexture("data/sample/texture/number005.png");
		}
		else
		{
			texID = pTex->LoadTexture("data/sample/texture/number004.png");
		}

		for (int nCount = 0; nCount < SCORE_NUM; nCount++)
		{
			m_pNumberList[nCount]->BindTexture(pTex->GetTexture(texID));
		}
	}
}

void CScoreManager::ResultScore()
{

	// ���݂̃X�R�A
	float startX = CApplication::SCREEN_SIDE_WIDTH;
	const float startY = 100;
	const float sizeX = 102;

	for (int x = 0; x < SCORE_NUM; x++)
	{
		auto pNum = CNumber::Create(D3DXVECTOR3(startX + x * sizeX, startY, 0));
		pNum->SetPosType(CObject2D::POSTYPE::LeftTop);
		pNum->SetSize(D3DXVECTOR2(sizeX, 204));
		pNum->SetNumber(0);
		m_pNumberList[SCORE_NUM - 1 - x] = pNum;
	}

	LatestScore();
}

void CScoreManager::LatestScore()
{
	// �X�R�A������̓_���ɑ����ɍX�V
	SetScore(m_destScore);
}

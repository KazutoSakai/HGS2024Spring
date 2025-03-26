
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
	// 現在のスコア
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
	// 目標スコアまで加算する
	if (m_score < m_destScore)
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

	// 桁数の処理
	int tmpScore = m_score;
	for (int i = 0; i < SCORE_NUM; i++)
	{
		auto pNum = m_pNumberList[i];

		int num = 0;

		// 1桁目を取得
		num = tmpScore % 10;

		// 1桁ずらす
		tmpScore /= 10;

		pNum->SetNumber(num);
	}
}

void CScoreManager::ResultScore()
{

	// 現在のスコア
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
	// スコアを現状の点数に即座に更新
	SetScore(m_destScore);
}

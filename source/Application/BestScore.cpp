
#include "BestScore.h"
#include "application.h"

#include "SceneGame.h"
#include "number.h"

#include "ScoreManager.h"

CBestScore::CBestScore()
{

}

HRESULT CBestScore::Init()
{
	// スコア読み取り
	m_BestScore = 0;
	FILE* pFile = nullptr;
	pFile = fopen("data/bestscore.txt", "r");
	if (pFile != nullptr)
	{
		auto ret = fscanf(pFile, "%d", &m_BestScore);
		fclose(pFile);
	}

	// 8桁分のナンバー
	const float sizeX = 28;
	const float startY = 0;
	float startX = SCREEN_WIDTH - CApplication::SCREEN_SIDE_WIDTH + sizeX* (SCORE_NUM - 1);
	int workScore = m_BestScore;
	for (int x = 0; x < SCORE_NUM; x++)
	{
		auto pNum = CNumber::Create(D3DXVECTOR3(startX - x * sizeX, startY, 0));
		pNum->SetPosType(CObject2D::POSTYPE::LeftTop);
		pNum->SetSize(D3DXVECTOR2(sizeX, 56));

		int score = workScore % 10;
		workScore /= 10;
		pNum->SetNumber(score);
	}

	return S_OK;
}

void CBestScore::Uninit()
{
	Release();
}

void CBestScore::Update()
{

}

void CBestScore::Draw()
{

}

CBestScore* CBestScore::Create()
{
	CBestScore* p = DBG_NEW CBestScore();

	p->Init();

	return p;
}

void CBestScore::SaveBestScore()
{
	// ベストスコアと今回のスコアを比較
	int curScore = CScoreManager::GetInstance()->GetScore();
	if (m_BestScore > curScore)
		return;

	// 今回のスコア書き出し
	FILE* pFile = nullptr;
	pFile = fopen("data/bestscore.txt", "w");
	if (pFile != nullptr)
	{
		auto ret = fprintf(pFile, "%d", curScore);
		fclose(pFile);
	}
}
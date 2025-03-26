
#include "Timer.h"
#include "application.h"

CTimer::CTimer()
{
	for (int i = 0; i < TIME_NUM; i++)
		m_pNumberList[i] = nullptr;

	m_time = 0;
	m_flgTimeRun = false;
}

CTimer::~CTimer()
{

}

HRESULT CTimer::Init()
{
	// 現在のスコア
	const float sizeX = 56;
	float startX = CApplication::SCREEN_SIDE_WIDTH - sizeX*TIME_NUM - sizeX;
	const float startY = 0;

	for (int x = 0; x < TIME_NUM; x++)
	{
		auto pNum = CNumber::Create(D3DXVECTOR3(startX + x * sizeX, startY, 0));
		pNum->SetPosType(CObject2D::POSTYPE::LeftTop);
		pNum->SetSize(D3DXVECTOR2(sizeX, sizeX*2));
		pNum->SetNumber(0);
		m_pNumberList[TIME_NUM - 1 - x] = pNum;
	}

	// 制限時間の残りタイム
	m_time = START_TIME;
	m_flgTimeRun = true;

	return S_OK;
}

void CTimer::Uninit()
{
	Release();
}

void CTimer::Update()
{
	if (m_flgTimeRun)
	{
		m_time -= GetWorldDeltaSeconds();

		SetTime((int)m_time);
	}
}

void CTimer::Draw()
{
	
}

CTimer* CTimer::Create()
{
	CTimer* p = DBG_NEW CTimer();

	p->Init();

	return p;
}

void CTimer::SetTime(int time)
{
	// 桁数の処理
	int tmpScore = time;
	for (int i = 0; i < TIME_NUM; i++)
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
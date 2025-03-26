
#include "RateBallManager.h"
#include "application.h"

#include "collision.h"

CRateBallManager::CRateBallManager()
{
	m_RateBallList.clear();
}

CRateBallManager::~CRateBallManager()
{

}

HRESULT CRateBallManager::Init()
{
	return S_OK;
}

void CRateBallManager::Uninit()
{
	for (auto it = m_RateBallList.begin(); it != m_RateBallList.end(); it++)
	{
		it->m_pRateBall->Uninit();
	}
	m_RateBallList.clear();
}

void CRateBallManager::Update()
{
	// ”{—¦‚½‚Ü‚ÌˆÊ’uÝ’è
	float startY = SCREEN_HEIGHT / 2;
	float startX = RATEBALL_SIZE / 2;
	int counter = 0;
	int xPos = 0;
	for (auto it = m_RateBallList.begin(); it != m_RateBallList.end(); it++)
	{
		xPos = (startX + counter * RATEBALL_SIZE);
		if (xPos + RATEBALL_SIZE >= CApplication::SCREEN_SIDE_WIDTH)
		{
			xPos = startX;
			counter = 0;
			startY += RATEBALL_SIZE;
		}

		it->m_pRateBall->SetPos(D3DXVECTOR3((float)(xPos), startY, 0));
		counter++;
	}
}

void CRateBallManager::Draw()
{

}


/// <summary>
/// ”{—¦‹Ê‚Ì•Û‘¶
/// </summary>
/// <param name="rate"></param>
void CRateBallManager::Regist(int rate)
{
	auto pTex = CApplication::GetInstance()->GetTexture();
	int texID = -1;

	switch (rate)
	{
	case 2:
		texID = pTex->LoadTexture("data/sample/texture/mag_2.png");
		break;
	case 3:
		texID = pTex->LoadTexture("data/sample/texture/mag_3.png");
		break;
	case 4:
		texID = pTex->LoadTexture("data/sample/texture/mag_4.png");
		break;
	case 5:
		texID = pTex->LoadTexture("data/sample/texture/mag_5.png");
		break;
	case 6:
		texID = pTex->LoadTexture("data/sample/texture/mag_6.png");
		break;
	case 7:
		texID = pTex->LoadTexture("data/sample/texture/mag_7.png");
		break;
	case 8:
		texID = pTex->LoadTexture("data/sample/texture/mag_8.png");
		break;
	case 9:
		texID = pTex->LoadTexture("data/sample/texture/mag_9.png");
		break;
	default:
		return;
	}

	RateBallInfo info =
	{
		texID,
		rate,
		nullptr
	};
	info.m_pRateBall = CObject2D::Create(CObject::Priority::UI);
	info.m_pRateBall->SetSize(D3DXVECTOR2(RATEBALL_SIZE, RATEBALL_SIZE));
	info.m_pRateBall->BindTexture(pTex->GetTexture(info.texId));

	m_RateBallList.push_back(info);
}
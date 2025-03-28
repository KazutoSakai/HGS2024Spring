
#include "BlockManager.h"
#include "application.h"

#include "collision.h"
#include "ScoreManager.h"
#include "SceneGame.h"

CBlockManager::CBlockManager()
{
	for (int i = 0; i < BLOCK_W * BLOCK_H; i++)
		m_pBlockList[i] = nullptr;
}

CBlockManager::~CBlockManager()
{
	
}

HRESULT CBlockManager::Init()
{
	// 仮でブロックを並べる
	float startPosX = CApplication::SCREEN_CENTER_X - (CBlock::BLOCK_SIZE_W * BLOCK_W / 2) + CBlock::BLOCK_SIZE_W / 2;
	float startPosY = SCREEN_HEIGHT / 5;
	for (int x = 0; x < BLOCK_W; x++)
	{
		for (int y = 0; y < BLOCK_H; y++)
		{
			auto pBlock = CBlock::Create();
			pBlock->SetPos(D3DXVECTOR3(startPosX + CBlock::BLOCK_SIZE_W * x, startPosY + CBlock::BLOCK_SIZE_H * y, 0));
			pBlock->SetColor(D3DCOLOR_ARGB(255,0,255,255));
			m_pBlockList[y*BLOCK_W + x] = pBlock;
		}
	}

	return S_OK;
}

void CBlockManager::Uninit()
{

}

void CBlockManager::Update()
{

}

void CBlockManager::Draw()
{

}

void CBlockManager::ReleaseBlock()
{
	for (int x = 0; x < BLOCK_W; x++)
	{
		for (int y = 0; y < BLOCK_H; y++)
		{
			int index = y * BLOCK_W + x;
			if (m_pBlockList[index] != nullptr)
			{
				m_pBlockList[index]->Uninit();
				m_pBlockList[index] = nullptr;
			}
		}
	}
}

bool CBlockManager::IsAllReleaseBlock()
{
	for (int i = 0; i < BLOCK_W * BLOCK_H; i++)
	{
		if (m_pBlockList[i] != nullptr)
		{
			return false;
		}
	}

	return true;
}

bool CBlockManager::CollisionBlock(const D3DXVECTOR3& pos, const D3DXVECTOR2& size, D3DXVECTOR3* pMove)
{
	CollisionSquare sq;

	CollisionCircle cr = 
	{
		pos.x, pos.y, size.x
	};

	D3DXVECTOR2 outMove = D3DXVECTOR2(pMove->x, pMove->y);

	for(int i = 0; i < BLOCK_W*BLOCK_H; i++)
	{
		auto pBlock = m_pBlockList[i];
		if (pBlock == nullptr)
			continue;

		const auto& bPos = pBlock->GetPos();
		auto size = pBlock->GetSize();
		sq.cx = bPos.x;
		sq.cy = bPos.y;
		sq.w = size.x;
		sq.h = size.y;
		sq.radian = 0.0f;
		
		// 四角形と点の当たり判定
		//if (CollisionSqVsPoint(sq, p))
		if(CollisionSqVsCircleReflection(sq, cr, &outMove))
		{
			// 反射は位置を加味して
			pMove->x = outMove.x;
			pMove->y = outMove.y;

			// ブロックは削除
			pBlock->Uninit();
			m_pBlockList[i] = nullptr;
			return true;
		}
	}

	return false;
}

CBlockManager* CBlockManager::Create()
{
	CBlockManager* p = DBG_NEW CBlockManager();

	p->Init();

	return p;
}
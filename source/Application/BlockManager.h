#ifndef _BLOCKMANAGER_H_
#define _BLOCKMANAGER_H_

#include "Block.h"
#include <vector>

class CBlockManager
{
public:

	//---------------------
	// Singleton
	static CBlockManager* GetInstance()
	{
		static CBlockManager instance;
		return &instance;
	}
	CBlockManager(const CBlockManager&) = delete;
	CBlockManager& operator=(const CBlockManager&) = delete;
	CBlockManager(CBlockManager&&) = delete;
	CBlockManager& operator=(CBlockManager&&) = delete;

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	bool CollisionBlock(const D3DXVECTOR3& pos, const D3DXVECTOR2& size, D3DXVECTOR3* pMove);

	static CBlockManager* Create();

private:
	static const int BLOCK_W = 11;
	static const int BLOCK_H = 6;

	//---------------------
	// default
	CBlockManager();					// コンストラクタ
	~CBlockManager();					// デストラクタ

	CBlock* m_pBlockList[BLOCK_W*BLOCK_H];

};

#endif
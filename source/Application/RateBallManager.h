#ifndef _RATEBALLMANAGER_H_
#define _RATEBALLMANAGER_H_

#include "Object2D.h"
#include <vector>

class CRateBallManager
{
public:

	//---------------------
	// Singleton
	static CRateBallManager* GetInstance()
	{
		static CRateBallManager instance;
		return &instance;
	}
	CRateBallManager(const CRateBallManager&) = delete;
	CRateBallManager& operator=(const CRateBallManager&) = delete;
	CRateBallManager(CRateBallManager&&) = delete;
	CRateBallManager& operator=(CRateBallManager&&) = delete;

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	void Regist(int rate);

private:

	//---------------------
	// default
	CRateBallManager();					// コンストラクタ
	~CRateBallManager();					// デストラクタ

	static const int RATEBALL_SIZE = 32;

	struct RateBallInfo
	{
		int texId;
		int rate;
		CObject2D* m_pRateBall;
	};

	std::vector<RateBallInfo> m_RateBallList;
};

#endif
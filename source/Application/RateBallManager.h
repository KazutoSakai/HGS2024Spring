#ifndef _RATEBALLMANAGER_H_
#define _RATEBALLMANAGER_H_

#include "Object2D.h"

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
	static const int SCORE_NUM = 8;

	//---------------------
	// default
	CRateBallManager();					// コンストラクタ
	~CRateBallManager();					// デストラクタ

	CObject2D* m_pRateBallList[SCORE_NUM];

};

#endif
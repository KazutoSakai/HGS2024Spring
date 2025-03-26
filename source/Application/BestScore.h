#ifndef _BESTSCORE_H_
#define _BESTSCORE_H_

#include "object2D.h"

class CBestScore : public CObject
{
public:
	CBestScore();
	~CBestScore() {};

	HRESULT Init() override;
	void Uninit();
	void Update();
	void Draw();

	void SaveBestScore();

	static CBestScore* Create();

private:
	static const int SCORE_NUM = 8;

	int m_BestScore;
};

#endif
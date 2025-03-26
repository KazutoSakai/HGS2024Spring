#ifndef _TIMER_H_
#define _TIMER_H_

#include "number.h"

class CTimer : public CObject
{
public:
	CTimer();					// �R���X�g���N�^
	~CTimer();					// �f�X�g���N�^

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	static CTimer* Create();

private:
	static const int TIME_NUM = 3;
	static const int START_TIME = 90;	// �b

	float m_time;
	CNumber* m_pNumberList[TIME_NUM];

	void SetTime(int time);

};

#endif
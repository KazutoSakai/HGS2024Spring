#ifndef _TIMER_H_
#define _TIMER_H_

#include "number.h"

class CTimer : public CObject
{
public:
	CTimer();					// コンストラクタ
	~CTimer();					// デストラクタ

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	static CTimer* Create();

	void StopTimer() { m_flgTimeRun = false; };

private:
	static const int TIME_NUM = 3;
	static const int START_TIME = 90;	// 秒

	float m_time;
	CNumber* m_pNumberList[TIME_NUM];

	void SetTime(int time);

	bool m_flgTimeRun;

};

#endif
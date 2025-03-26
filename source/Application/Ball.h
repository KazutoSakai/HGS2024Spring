#ifndef _BALL_H_
#define _BALL_H_

#include "object2D.h"
#include "sound.h"

class CBall : public CObject2D
{
public:
	CBall();
	~CBall() {};

	HRESULT Init() override;
	void Uninit();
	void Update();
	void CollisionUpdate();
	void Draw();

	static CBall* Create();

	void SetPlayerID(int id) { m_PlayerID = id; }

private:
	static const int MOVE_POWER = 5;
	D3DXVECTOR3 m_move;

	CSound* m_pBallSound;					// ボール用のサウンド
	int m_PlayerID;
	int isVsPlayerDoneCounter = 0;		// 前回のフレームでプレイヤーと当たり判定したか

	// 倍率
	static const int RATE_MAX = 9;
	static const int DEFAULT_RATE = 1;
	int m_NumRate;				// 1～9
	int m_NumRateID[RATE_MAX];
};

#endif
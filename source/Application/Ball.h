#ifndef _BALL_H_
#define _BALL_H_

#include "object2D.h"

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

	int m_PlayerID;

	int isVsPlayerDoneCounter = 0;		// 前回のフレームでプレイヤーと当たり判定したか

};

#endif
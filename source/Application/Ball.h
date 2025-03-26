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

	CSound* m_pBallSound;					// �{�[���p�̃T�E���h
	int m_PlayerID;
	int isVsPlayerDoneCounter = 0;		// �O��̃t���[���Ńv���C���[�Ɠ����蔻�肵����
};

#endif
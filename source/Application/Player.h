#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "object2D.h"

class CPlayer : public CObject2D
{
public:
	CPlayer();
	~CPlayer() {};

	HRESULT Init() override;
	void Uninit();
	void Update();
	void Draw();

	static CPlayer* Create();

private:
	static const int MOVE_POWER = 8;
};

#endif
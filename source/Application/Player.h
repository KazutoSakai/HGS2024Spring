#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "object2D.h"

class CPlayer : public CObject2D
{
public:

	enum class ColorState
	{
		DEFAULT,
		GREEN,
		RED,
	};

	CPlayer();
	~CPlayer() {};

	HRESULT Init() override;
	void Uninit();
	void Update();
	void Draw();

	static CPlayer* Create();

	void SetColorState(ColorState state);

private:
	static const int MOVE_POWER = 8;

	ColorState m_ColorState;
	float m_ColorTimer = 0;
};

#endif
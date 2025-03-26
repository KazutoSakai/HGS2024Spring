#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "object2D.h"

class CBlock : public CObject2D
{
public:
	static const int BLOCK_SIZE_W = 64;
	static const int BLOCK_SIZE_H = 32;

	CBlock();
	~CBlock() {};

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	static CBlock* Create();

private:

};

#endif
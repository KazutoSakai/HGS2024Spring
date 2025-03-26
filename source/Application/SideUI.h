#ifndef _SIDEUI_H_
#define _SIDEUI_H_

#include "object2D.h"

class CSideUI : public CObject2D
{
public:
	CSideUI();
	~CSideUI() {};

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	static CSideUI* Create(bool isLeft);

private:

};

#endif
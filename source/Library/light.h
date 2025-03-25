//*********************************************
//
// ���C�g(light.h)
// Author : Junichi Uchiyama
//
//*********************************************

#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "main.h"

/// <summary>
/// ���C�g
/// </summary>
class CLight
{
private:
	static const int MAX_LIGHT = 2;

public:
	CLight();			// �R���X�g���N�^
	~CLight() {};		// �f�X�g���N�^

	HRESULT Init();		// ������

private:
	D3DLIGHT9 m_Light[MAX_LIGHT];	// ���C�g���
};

#endif
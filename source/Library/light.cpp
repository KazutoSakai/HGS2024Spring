//*********************************************
//
// ���C�g(light.cpp)
// Author : Junichi Uchiyama
//
//*********************************************

#include "light.h"
#include "application.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
CLight::CLight()
{
	// ���C�g�̏�����
	ZeroMemory(&m_Light[0], sizeof(D3DLIGHT9)*MAX_LIGHT);
}

/// <summary>
/// ������
/// </summary>
/// <returns></returns>
HRESULT CLight::Init()
{
	CRenderer* pRenderer = CApplication::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXVECTOR3 dir[MAX_LIGHT]{ D3DXVECTOR3(0,0,-100),  D3DXVECTOR3(0, -100, 100) };	// ���C�g�����x�N�g��

	for (int i = 0; i < MAX_LIGHT; i++)
	{
		// ���C�g�̎��
		m_Light[i].Type = D3DLIGHT_DIRECTIONAL;	// ���s����

		// �g�U��
		m_Light[i].Diffuse = D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.2f);

		// ���C�g�����̐ݒ�
		D3DXVec3Normalize(&dir[i], &dir[i]);			// ���K��
		m_Light[i].Direction = dir[i];

		// ���C�g�̐ݒ�
		pDevice->SetLight(i, &m_Light[i]);

		// ���C�g�̗L����
		pDevice->LightEnable(i, TRUE);
	}

	// ����
	//D3DXCOLOR ambient = D3DXCOLOR(0.3f, 0.3f, 0.3f, 0.3f);

	//pDevice->SetRenderState(
	//	D3DRS_AMBIENT,
	//	ambient
	//);

	return S_OK;
}
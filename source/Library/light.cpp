//*********************************************
//
// ライト(light.cpp)
// Author : Junichi Uchiyama
//
//*********************************************

#include "light.h"
#include "application.h"

/// <summary>
/// コンストラクタ
/// </summary>
CLight::CLight()
{
	// ライトの初期化
	ZeroMemory(&m_Light[0], sizeof(D3DLIGHT9)*MAX_LIGHT);
}

/// <summary>
/// 初期化
/// </summary>
/// <returns></returns>
HRESULT CLight::Init()
{
	CRenderer* pRenderer = CApplication::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXVECTOR3 dir[MAX_LIGHT]{ D3DXVECTOR3(0,0,-100),  D3DXVECTOR3(0, -100, 100) };	// ライト方向ベクトル

	for (int i = 0; i < MAX_LIGHT; i++)
	{
		// ライトの種類
		m_Light[i].Type = D3DLIGHT_DIRECTIONAL;	// 平行光源

		// 拡散光
		m_Light[i].Diffuse = D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.2f);

		// ライト方向の設定
		D3DXVec3Normalize(&dir[i], &dir[i]);			// 正規化
		m_Light[i].Direction = dir[i];

		// ライトの設定
		pDevice->SetLight(i, &m_Light[i]);

		// ライトの有効化
		pDevice->LightEnable(i, TRUE);
	}

	// 環境光
	//D3DXCOLOR ambient = D3DXCOLOR(0.3f, 0.3f, 0.3f, 0.3f);

	//pDevice->SetRenderState(
	//	D3DRS_AMBIENT,
	//	ambient
	//);

	return S_OK;
}
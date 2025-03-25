//*********************************************
//
// エフェクト(effect.cpp)
// Author : Junichi Uchiyama
//
//*********************************************

#include "effect.h"
#include "application.h"
#include "renderer.h"

LPDIRECT3DTEXTURE9 CEffect::m_pTexture = nullptr;

//------------------------------------
// コンストラクタ
//------------------------------------
CEffect::CEffect(Priority priority) :CObject2D(priority), m_life(0)
{

}

//------------------------------------
// デストラクタ
//------------------------------------
CEffect::~CEffect()
{

}

//------------------------------------
// 初期化
//------------------------------------
HRESULT CEffect::Init()
{
	CObject2D::Init();

	CObject2D::SetSize(D3DXVECTOR2(50.0f, 50.0f));

	// テクスチャ
	auto pTex = CApplication::GetInstance()->GetTexture();
	int id = pTex->LoadTexture("data/sample/texture/effect000.jpg");
	m_pTexture = pTex->GetTexture(id);
	BindTexture(m_pTexture);

	CObject2D::UpdateVertex();

	return S_OK;
}

//------------------------------------
// 解放
//------------------------------------
void CEffect::Uninit()
{
	CObject2D::Uninit();
}

//------------------------------------
// 更新
//------------------------------------
void CEffect::Update()
{
	D3DXCOLOR col = GetColor();
	D3DXVECTOR3 scale = GetScale();

	// 寿命
	m_life--;
	if (m_life <= 0)
	{
		Uninit();
		return;
	}

	// 減衰
	float rate = 0.05f;
	col.a += (0 - col.a) * rate;
	scale.x += (0 - scale.x) * rate;
	scale.y += (0 - scale.y) * rate;

	SetColor(col);
	SetScale(scale);

	CObject2D::Update();
}

//------------------------------------
// 描画
//------------------------------------
void CEffect::Draw()
{
	CRenderer* pRender = CApplication::GetInstance()->GetRenderer();

	pRender->SetRenderState(CRenderer::RENDER_STATE::ADD);

	CObject2D::Draw();

	pRender->SetRenderState(CRenderer::RENDER_STATE::DEFAULT);
}

////------------------------------------
//// テクスチャ読込
////------------------------------------
//HRESULT CEffect::Load()
//{
//	CRenderer* pRenderer = CApplication::GetInstance()->GetRenderer();
//	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
//
//	return S_OK;
//}

////------------------------------------
//// テクスチャ破棄
////------------------------------------
//void CEffect::UnLoad()
//{
//	if (m_pTexture != nullptr)
//	{
//		m_pTexture->Release();
//		m_pTexture = nullptr;
//	}
//}

//------------------------------------
// 生成
//------------------------------------
CEffect* CEffect::Create(const D3DXVECTOR3& pos, const D3DXCOLOR& col, int life)
{
	CEffect* pEffect;

	pEffect = DBG_NEW CEffect();

	pEffect->SetPos(pos);
	pEffect->SetLife(life);
	pEffect->SetColor(col);

	pEffect->Init();

	return pEffect;
}

//------------------------------------
// 寿命設定
//------------------------------------
void CEffect::SetLife(int life)
{
	m_life = life;
}

//------------------------------------
// 寿命取得
//------------------------------------
int CEffect::GetLife()
{
	return m_life;
}
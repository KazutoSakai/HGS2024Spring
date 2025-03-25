//*********************************************
//
// �G�t�F�N�g(effect.cpp)
// Author : Junichi Uchiyama
//
//*********************************************

#include "effect.h"
#include "application.h"
#include "renderer.h"

LPDIRECT3DTEXTURE9 CEffect::m_pTexture = nullptr;

//------------------------------------
// �R���X�g���N�^
//------------------------------------
CEffect::CEffect(Priority priority) :CObject2D(priority), m_life(0)
{

}

//------------------------------------
// �f�X�g���N�^
//------------------------------------
CEffect::~CEffect()
{

}

//------------------------------------
// ������
//------------------------------------
HRESULT CEffect::Init()
{
	CObject2D::Init();

	CObject2D::SetSize(D3DXVECTOR2(50.0f, 50.0f));

	// �e�N�X�`��
	auto pTex = CApplication::GetInstance()->GetTexture();
	int id = pTex->LoadTexture("data/sample/texture/effect000.jpg");
	m_pTexture = pTex->GetTexture(id);
	BindTexture(m_pTexture);

	CObject2D::UpdateVertex();

	return S_OK;
}

//------------------------------------
// ���
//------------------------------------
void CEffect::Uninit()
{
	CObject2D::Uninit();
}

//------------------------------------
// �X�V
//------------------------------------
void CEffect::Update()
{
	D3DXCOLOR col = GetColor();
	D3DXVECTOR3 scale = GetScale();

	// ����
	m_life--;
	if (m_life <= 0)
	{
		Uninit();
		return;
	}

	// ����
	float rate = 0.05f;
	col.a += (0 - col.a) * rate;
	scale.x += (0 - scale.x) * rate;
	scale.y += (0 - scale.y) * rate;

	SetColor(col);
	SetScale(scale);

	CObject2D::Update();
}

//------------------------------------
// �`��
//------------------------------------
void CEffect::Draw()
{
	CRenderer* pRender = CApplication::GetInstance()->GetRenderer();

	pRender->SetRenderState(CRenderer::RENDER_STATE::ADD);

	CObject2D::Draw();

	pRender->SetRenderState(CRenderer::RENDER_STATE::DEFAULT);
}

////------------------------------------
//// �e�N�X�`���Ǎ�
////------------------------------------
//HRESULT CEffect::Load()
//{
//	CRenderer* pRenderer = CApplication::GetInstance()->GetRenderer();
//	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
//
//	return S_OK;
//}

////------------------------------------
//// �e�N�X�`���j��
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
// ����
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
// �����ݒ�
//------------------------------------
void CEffect::SetLife(int life)
{
	m_life = life;
}

//------------------------------------
// �����擾
//------------------------------------
int CEffect::GetLife()
{
	return m_life;
}
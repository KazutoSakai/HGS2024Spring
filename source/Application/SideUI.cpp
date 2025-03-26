
#include "SideUI.h"
#include "application.h"

CSideUI::CSideUI()
{

}

HRESULT CSideUI::Init()
{
	CObject2D::Init();

	// (x, y) = (���A�c)
	SetSize(D3DXVECTOR2(CApplication::SCREEN_SIDE_WIDTH, SCREEN_HEIGHT));

	return S_OK;
}

void CSideUI::Uninit()
{
	CObject2D::Uninit();
}

void CSideUI::Update()
{
	CObject2D::Update();
}

void CSideUI::Draw()
{
	CObject2D::Draw();
}

CSideUI* CSideUI::Create(bool isLeft)
{
	CSideUI* p = DBG_NEW CSideUI();

	p->Init();

	if (isLeft)
	{
		// �e�N�X�`��
		auto pTex = CApplication::GetInstance()->GetTexture();
		int id = pTex->LoadTexture("data/sample/texture/side_L.png");
		p->BindTexture(pTex->GetTexture(id));
		// �ʒu
		p->SetPosType(CObject2D::POSTYPE::LeftTop);
		p->SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
	else
	{
		// �e�N�X�`��
		auto pTex = CApplication::GetInstance()->GetTexture();
		int id = pTex->LoadTexture("data/sample/texture/side_R.png");
		p->BindTexture(pTex->GetTexture(id));
		// �ʒu
		p->SetPosType(CObject2D::POSTYPE::LeftTop);
		p->SetPos(D3DXVECTOR3(SCREEN_WIDTH - CApplication::SCREEN_SIDE_WIDTH, 0.0f, 0.0f));
	}

	return p;
}
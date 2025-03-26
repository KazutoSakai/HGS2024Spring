
#include "Block.h"
#include "application.h"

CBlock::CBlock()
{

}

HRESULT CBlock::Init()
{
	CObject2D::Init();

	// �ʒu�ݒ�B��_�͒��S���f�t�H�B
	SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT / 5 * 4, 0.0f));
	// (x, y) = (���A�c)
	SetSize(D3DXVECTOR2(BLOCK_SIZE_W, BLOCK_SIZE_H));

	// �e�N�X�`��
	auto pTex = CApplication::GetInstance()->GetTexture();
	int id = pTex->LoadTexture("data/sample/texture/block_3.png");
	BindTexture(pTex->GetTexture(id));

	return S_OK;
}

void CBlock::Uninit()
{
	CObject2D::Uninit();
}

void CBlock::Update()
{
	CObject2D::Update();
}

void CBlock::Draw()
{
	CObject2D::Draw();
}

CBlock* CBlock::Create()
{
	CBlock* p = DBG_NEW CBlock();

	p->Init();

	return p;
}
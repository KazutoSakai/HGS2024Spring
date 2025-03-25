//*********************************************
//
// �X�e���V��(stencil.cpp)
// Author : Junichi Uchiyama
//
//*********************************************

#include "stencil.h"
#include "application.h"

/// <summary>
/// �X�e���V���ݒ�J�n
/// </summary>
/// <param name="type"></param>
void CStencil::Begine(STENCIL_TYPE type)
{
	CRenderer* pRenderer = CApplication::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	if (type < 0)
	{
		return;
	}

	// �X�e���V���e�X�g�̌��ʂɑ΂��Ă̔��f�ݒ�
	if (type == STENCIL_TYPE::BASE)
	{
		// �X�e���V���o�b�t�@ => �L��
		pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);

		// �X�e���V���o�b�t�@�Ɣ�r����Q�ƒl�ݒ� => ref
		pDevice->SetRenderState(D3DRS_STENCILREF, 1);

		// �X�e���V���o�b�t�@�̒l�ɑ΂��Ẵ}�X�N�ݒ� => 0xff(�S�Đ^)
		pDevice->SetRenderState(D3DRS_STENCILMASK, 0xff);

		// �X�e���V���e�X�g�̔�r���@�ݒ� => 
		// (�Q�ƒl >= �X�e���V���o�b�t�@�̎Q�ƒl)�@�Ȃ獇�i
		pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_GREATEREQUAL);

		pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);
		pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
		pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
	}
	else if (type == STENCIL_TYPE::OVERLAP)
	{
		// �X�e���V���o�b�t�@ => �L��
		pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);

		// �X�e���V���o�b�t�@�Ɣ�r����Q�ƒl�ݒ� => ref
		pDevice->SetRenderState(D3DRS_STENCILREF, 1);

		// �X�e���V���o�b�t�@�̒l�ɑ΂��Ẵ}�X�N�ݒ� => 0xff(�S�Đ^)
		pDevice->SetRenderState(D3DRS_STENCILMASK, 0xff);

		// �X�e���V���e�X�g�̔�r���@�ݒ� => 
		// (�Q�ƒl >= �X�e���V���o�b�t�@�̎Q�ƒl)�@�Ȃ獇�i
		pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);

		pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR);
		pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
		pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
	}
	else if (type == STENCIL_TYPE::COLORPOLYGON)
	{
		// �X�e���V���o�b�t�@ => �L��
		pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);

		// �X�e���V���o�b�t�@�Ɣ�r����Q�ƒl�ݒ� => ref
		pDevice->SetRenderState(D3DRS_STENCILREF, 2);

		// �X�e���V���o�b�t�@�̒l�ɑ΂��Ẵ}�X�N�ݒ� => 0xff(�S�Đ^)
		pDevice->SetRenderState(D3DRS_STENCILMASK, 0xff);

		// �X�e���V���e�X�g�̔�r���@�ݒ� => 
		// (�Q�ƒl >= �X�e���V���o�b�t�@�̎Q�ƒl)�@�Ȃ獇�i
		pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);

		pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);
		pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
		pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
	}
}

/// <summary>
/// �X�e���V���I��
/// </summary>
void CStencil::End()
{
	CRenderer* pRenderer = CApplication::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
}
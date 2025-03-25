//*********************************************
//
// ステンシル(stencil.cpp)
// Author : Junichi Uchiyama
//
//*********************************************

#include "stencil.h"
#include "application.h"

/// <summary>
/// ステンシル設定開始
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

	// ステンシルテストの結果に対しての反映設定
	if (type == STENCIL_TYPE::BASE)
	{
		// ステンシルバッファ => 有効
		pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);

		// ステンシルバッファと比較する参照値設定 => ref
		pDevice->SetRenderState(D3DRS_STENCILREF, 1);

		// ステンシルバッファの値に対してのマスク設定 => 0xff(全て真)
		pDevice->SetRenderState(D3DRS_STENCILMASK, 0xff);

		// ステンシルテストの比較方法設定 => 
		// (参照値 >= ステンシルバッファの参照値)　なら合格
		pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_GREATEREQUAL);

		pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);
		pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
		pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
	}
	else if (type == STENCIL_TYPE::OVERLAP)
	{
		// ステンシルバッファ => 有効
		pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);

		// ステンシルバッファと比較する参照値設定 => ref
		pDevice->SetRenderState(D3DRS_STENCILREF, 1);

		// ステンシルバッファの値に対してのマスク設定 => 0xff(全て真)
		pDevice->SetRenderState(D3DRS_STENCILMASK, 0xff);

		// ステンシルテストの比較方法設定 => 
		// (参照値 >= ステンシルバッファの参照値)　なら合格
		pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);

		pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR);
		pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
		pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
	}
	else if (type == STENCIL_TYPE::COLORPOLYGON)
	{
		// ステンシルバッファ => 有効
		pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);

		// ステンシルバッファと比較する参照値設定 => ref
		pDevice->SetRenderState(D3DRS_STENCILREF, 2);

		// ステンシルバッファの値に対してのマスク設定 => 0xff(全て真)
		pDevice->SetRenderState(D3DRS_STENCILMASK, 0xff);

		// ステンシルテストの比較方法設定 => 
		// (参照値 >= ステンシルバッファの参照値)　なら合格
		pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);

		pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);
		pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
		pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
	}
}

/// <summary>
/// ステンシル終了
/// </summary>
void CStencil::End()
{
	CRenderer* pRenderer = CApplication::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
}
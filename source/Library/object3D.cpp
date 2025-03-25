//*********************************************
//
// 3Dオブジェクト(object3D.cpp)
// Author : Junichi Uchiyama
//
//*********************************************

#include "object3D.h"
#include "application.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="priority">描画優先</param>
CObject3D::CObject3D(Priority priority) : CObject(priority)
{
	D3DXMatrixIdentity(&m_WorldMat);
}

/// <summary>
/// デストラクタ
/// </summary>
CObject3D::~CObject3D()
{

}

/// <summary>
/// 解放
/// </summary>
void CObject3D::Uninit()
{
	Release();
}

/// <summary>
/// 更新
/// </summary>
void CObject3D::Update()
{
	// ワールド行列作成
	UpdateWorldMatrix();
}

/// <summary>
/// ワールド行列作成
/// </summary>
void CObject3D::UpdateWorldMatrix()
{
	D3DXMATRIX worldMat;

	// ワールド行列の初期化
	D3DXMatrixIdentity(&worldMat);

	// スケール行列の設定
	UpdateScaling(&worldMat);

	// 回転行列の設定（ヨー・ピッチ・ロール）
	UpdateRotation(&worldMat);

	// 移動行列の設定
	UpdateTranslation(&worldMat);

	// ワールド行列の設定
	SetWorldMat(worldMat);
}

/// <summary>
/// ワールドマトリクス取得
/// </summary>
/// <returns></returns>
const D3DXMATRIX& CObject3D::GetWorldMat() const
{
	return m_WorldMat;
}

/// <summary>
/// ワールドマトリクス設定
/// </summary>
/// <param name="mat"></param>
void CObject3D::SetWorldMat(const D3DXMATRIX& mat)
{
	m_WorldMat = mat;
}

/// <summary>
/// 回転マトリクス取得
/// </summary>
/// <returns></returns>
const D3DXMATRIX& CObject3D::GetRotMat() const
{
	return m_RotMat;
}

void CObject3D::UpdateScaling(D3DXMATRIX* pOut)
{
	D3DXMATRIX scaleMtx;

	D3DXVECTOR3 scale = GetScale();
	D3DXMatrixScaling(&scaleMtx, scale.x, scale.y, scale.z);
	D3DXMatrixMultiply(pOut, pOut, &scaleMtx);
}

void CObject3D::UpdateRotation(D3DXMATRIX* pOut)
{
	//D3DXMATRIX rotMtx;

	D3DXVECTOR3 rot = GetRot();
	D3DXMatrixRotationYawPitchRoll(&m_RotMat, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(pOut, pOut, &m_RotMat);
}

void CObject3D::UpdateTranslation(D3DXMATRIX* pOut)
{
	D3DXMATRIX transMtx;

	D3DXVECTOR3 pos = GetPos();
	D3DXMatrixTranslation(&transMtx, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(pOut, pOut, &transMtx);
}
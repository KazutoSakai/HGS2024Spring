//*********************************************
//
// 3D�I�u�W�F�N�g(object3D.cpp)
// Author : Junichi Uchiyama
//
//*********************************************

#include "object3D.h"
#include "application.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="priority">�`��D��</param>
CObject3D::CObject3D(Priority priority) : CObject(priority)
{
	D3DXMatrixIdentity(&m_WorldMat);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CObject3D::~CObject3D()
{

}

/// <summary>
/// ���
/// </summary>
void CObject3D::Uninit()
{
	Release();
}

/// <summary>
/// �X�V
/// </summary>
void CObject3D::Update()
{
	// ���[���h�s��쐬
	UpdateWorldMatrix();
}

/// <summary>
/// ���[���h�s��쐬
/// </summary>
void CObject3D::UpdateWorldMatrix()
{
	D3DXMATRIX worldMat;

	// ���[���h�s��̏�����
	D3DXMatrixIdentity(&worldMat);

	// �X�P�[���s��̐ݒ�
	UpdateScaling(&worldMat);

	// ��]�s��̐ݒ�i���[�E�s�b�`�E���[���j
	UpdateRotation(&worldMat);

	// �ړ��s��̐ݒ�
	UpdateTranslation(&worldMat);

	// ���[���h�s��̐ݒ�
	SetWorldMat(worldMat);
}

/// <summary>
/// ���[���h�}�g���N�X�擾
/// </summary>
/// <returns></returns>
const D3DXMATRIX& CObject3D::GetWorldMat() const
{
	return m_WorldMat;
}

/// <summary>
/// ���[���h�}�g���N�X�ݒ�
/// </summary>
/// <param name="mat"></param>
void CObject3D::SetWorldMat(const D3DXMATRIX& mat)
{
	m_WorldMat = mat;
}

/// <summary>
/// ��]�}�g���N�X�擾
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
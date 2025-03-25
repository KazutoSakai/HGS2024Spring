//*********************************************
//
// 3D�I�u�W�F�N�g(object3D.h)
// Author : Junichi Uchiyama
//
//*********************************************

#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

#include "object.h"

#define FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)	// ���W�A�@���A�J���[�A�e�N�X�`��

/// <summary>
/// ���_���3D
/// </summary>
typedef struct
{
	D3DXVECTOR3 pos;		// ���_���W
	D3DXVECTOR3 nor;		// �@��
	DWORD col;				// ���_�J���[
	D3DXVECTOR2 tex;		// �e�N�X�`�����W
}VERTEX_3D;

/// <summary>
/// 3D�I�u�W�F�N�g�ɕK�v�ȏ������������ۃN���X
/// </summary>
class CObject3D : public CObject
{
public:
	//---------------------
	// public Method
	CObject3D(Priority priority = Priority::Default);		// �R���X�g���N�^
	~CObject3D() override;									// �f�X�g���N�^

	HRESULT Init() = 0;										// �������i�������j
	void Uninit() override;									// ���
	void Update() override;									// �X�V
	virtual void Draw() = 0;								// �`��
	void UpdateWorldMatrix();								// ���[���h�s��쐬

	//---------------------
	// Getter Setter
	const D3DXMATRIX& GetWorldMat() const;		// ���[���h�}�g���N�X�擾
	void SetWorldMat(const D3DXMATRIX& mat);	// ���[���h�}�g���N�X�ݒ�

	const D3DXMATRIX& GetRotMat() const;		// ��]�s��̎擾

protected:
	//---------------------
	// protected Method�i�I�[�o�[���C�h�\�j
	virtual void UpdateScaling(D3DXMATRIX* pOut);
	virtual void UpdateRotation(D3DXMATRIX* pOut);
	virtual void UpdateTranslation(D3DXMATRIX* pOut);

private:
	//---------------------
	// private Method
	D3DXMATRIX m_WorldMat;	// ���[���h�}�g���N�X
	D3DXMATRIX m_RotMat;	// ��]�s��
};

#endif
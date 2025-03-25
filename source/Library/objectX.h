//*********************************************
//
// �I�u�W�F�N�gX(objectX.h)
// Author : Junichi Uchiyama
//
//*********************************************

#ifndef _OBJECTX_H_
#define _OBJECTX_H_

#include "object3D.h"

/// <summary>
/// X�t�@�C����ǂݍ��ݕ`�悷��
/// </summary>
class CObjectX : public CObject3D
{
public:
	//---------------------
	// public Method
	CObjectX(Priority priority = Priority::Default);		// �R���X�g���N�^
	~CObjectX() override;									// �f�X�g���N�^

	HRESULT Init() override;								// ������
	void Uninit() override;									// ���
	void Update() override;									// �X�V
	void Draw() override;									// �`��
	HRESULT LoadXFile(const char* filename);				// X�t�@�C���Ǎ�
	void SetColor(const D3DXCOLOR& col) override;			// �J���[���㏑������
	void BindTexture(LPDIRECT3DTEXTURE9 pTex);				// �e�N�X�`���𔽉f

	//---------------------
	// static Method
	static CObjectX* Create(const D3DXVECTOR3& pos, const char* filename);

	//---------------------
	// Getter Setter
	D3DXVECTOR3& GetLocalMin() { return m_vtxLocalMin; }
	D3DXVECTOR3& GetLocalMax() { return m_vtxLocalMax; }

private:
	//---------------------
	// private Member
	LPD3DXMESH m_pMesh;				// ���b�V�����
	LPD3DXBUFFER m_pMaterialBuf;	// �}�e���A�����
	DWORD m_MaterialNum;			// �}�e���A����

	D3DXVECTOR3 m_vtxLocalMin;		// ���_�ŏ����W
	D3DXVECTOR3 m_vtxLocalMax;		// ���_�ő���W

	LPDIRECT3DTEXTURE9 m_pTexture;	// �e�N�X�`��
};

#endif
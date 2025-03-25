//*********************************************
//
// �|���S���`��(object2D.h)
// Author : Junichi Uchiyama
//
//*********************************************

#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_

#include "object.h"

#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)	// ���_�t�H�[�}�b�g

// ���_���[2D]
typedef struct
{
	D3DXVECTOR3 pos;		// ���_���W
	float rhw;				// ���W�ϊ��p�W���i1.0f)
	D3DCOLOR col;			// ���_�J���[
	D3DXVECTOR2 tex;		// �e�N�X�`�����W
}VERTEX_2D;

// �e�N�X�`�����W�Ǘ�
typedef struct
{
	float leftU;		// ����U
	float topV;			// �E��V
	float rightU;		// ����U
	float bottomV;		// �E��V
}TEXTURE_UV;

/// <summary>
/// 2D�I�u�W�F�N�g
/// </summary>
class CObject2D : public CObject
{
public:
	//---------------------
	// enum

	// �A���J�[�|�C���g��ݒ�
	enum class POSTYPE
	{
		Center,
		Under,
		LeftTop,

		Max
	};

	//---------------------
	// public Method
	CObject2D(CObject::Priority priority = Priority::Default);		// �R���X�g���N�^
	~CObject2D() override;		// �f�X�g���N�^

	HRESULT Init() override;		// ������
	void Uninit() override;			// �I��
	void Update() override;			// �X�V
	void Draw() override;			// �`��
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);		// �e�N�X�`�����f
	void UpdateVertex();			// ���_�X�V

	//---------------------
	// static Method
	static CObject2D* Create(CObject::Priority priority = Priority::Default);

	//---------------------
	// Getter
	const D3DXVECTOR2& GetSize() const;			// �T�C�Y�擾
	void SetSize(const D3DXVECTOR2& size);		// �T�C�Y�ݒ�

	const TEXTURE_UV& GetUV() const;			// �e�N�X�`�����W�擾
	void SetUV(const TEXTURE_UV& uv);			// �e�N�X�`�����W�ݒ�

	const POSTYPE& GetPosType() const;			// ���_�ʒu�̐ݒ���@
	void SetPosType(const POSTYPE& type);		// ���_�ʒu�̐ݒ���@

private:
	//---------------------
	// private Member
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuf;		// ���_�o�b�t�@
	LPDIRECT3DTEXTURE9 m_pTexture;			// �e�N�X�`��

	D3DXVECTOR2 m_size;						// �c���T�C�Y
	TEXTURE_UV m_uv;						// �e�N�X�`�����W
	POSTYPE m_posType;						// ���_�ʒu�̐ݒ���@
};

#endif
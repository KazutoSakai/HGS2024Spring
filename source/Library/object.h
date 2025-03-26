//*********************************************
//
// �I�u�W�F�N�g(object.h)
// Author : Junichi Uchiyama
//
//*********************************************

#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "main.h"
#include "stencil.h"

/// <summary>
/// �I�u�W�F�N�g�N���X
/// </summary>
class CObject
{
public:

	//---------------------
	// �萔
	static const int MAX_OBJ = 128;

	//---------------------
	// enum

	// �I�u�W�F�N�g�^�C�v
	enum ObjType
	{
		DEFAULT,	// ����
		PLAYER,		// �v���C���[

		MAX,		// �ő吔
		INVALID,	// ����ID
	};

	// �`��D��x
	enum Priority
	{
		View = 0,
		UltraLow,
		Low,
		Default = 3,
		Object,
		Effect_Low,
		Character,
		Effect_Up,
		UI,

		Max
	};

	//---------------------
	// public Method
	CObject(Priority priority = Priority::Default);		// �R���X�g���N�^
	virtual ~CObject();									// �f�X�g���N�^

	virtual HRESULT Init() = 0;							// ������
	virtual void Uninit() = 0;							// �j���iRelease()������ŌĂяo�����Ƃō폜�����j
	virtual void Update() = 0;							// �X�V
	virtual void Draw() = 0;							// �`��
	virtual void DebugDraw();							// �f�o�b�O�`��

	//---------------------
	// static Method
	static void ReleaseAll();							// �Ǘ��I�u�W�F�N�g�̉��
	static void UpdateAll();							// �Ǘ��I�u�W�F�N�g�̍X�V
	static void DrawAll();								// �Ǘ��I�u�W�F�N�g�̕`��
	static void DrawDebugAll();							// �Ǘ��I�u�W�F�N�g�̃f�o�b�O�`��
	static CObject* GetObj(Priority priority, int idx);	// �I�u�W�F�N�g�擾

	//---------------------
	// Getter
	ObjType GetObjType() const;							// �I�u�W�F�N�g�^�C�v�擾
	void SetObjType(ObjType type);						// �I�u�W�F�N�g��ݒ�

	const D3DXVECTOR3& GetPos() const;					// ���W�擾
	void SetPos(const D3DXVECTOR3& pos);				// ���W�ݒ�

	const D3DXVECTOR3& GetRot() const;					// ��]�擾
	void SetRot(const D3DXVECTOR3& rot);				// ��]�ݒ�

	const D3DXVECTOR3& GetScale() const;				// �X�P�[���擾
	void SetScale(const D3DXVECTOR3& scale);			// �X�P�[���ݒ�
	
	bool IsUpdate();									// �X�V���邩�擾
	void SetIsUpdate(bool flg);							// �X�V���邩�ݒ�

	CStencil::STENCIL_TYPE GetStencilType();			// �X�e���V���o�b�t�@�擾
	void SetStencilType(CStencil::STENCIL_TYPE type);	// �X�e���V���o�b�t�@�ݒ�

	virtual const D3DXCOLOR& GetColor() const;			// �J���[�擾
	virtual void SetColor(const D3DXCOLOR& col);		// �J���[�ݒ�

	int GetId();										// ID�擾

	void SetFlgManualDelete(bool manual);			// �蓮�ł̍폜�����邩

protected:

	//---------------------
	// protected Method
	void Release();										// ���g�����

private:
	//---------------------
	// private Member

	static CObject* m_apObject[Priority::Max][MAX_OBJ];	// �Ǘ��I�u�W�F�N�g
	static int m_nNumAll;								// �Ǘ��I�u�W�F�N�g����
	Priority m_priority;								// �D�揇�ʂ̔ԍ�

	int m_ID;											// ���ʔԍ�;
	ObjType m_objType;									// �I�u�W�F�N�g�̎��

	D3DXVECTOR3 m_pos;									// ���W
	D3DXVECTOR3 m_rot;									// ��]
	D3DXVECTOR3 m_scale;								// �X�P�[��
	D3DXCOLOR m_color;									// �J���[

	bool m_IsUpdate;									// �X�V�������s�����ۂ�
	CStencil::STENCIL_TYPE m_StencilBufType;			// �X�e���V���o�b�t�@�^�C�v

	bool m_FlgManualRelease;							// ���̃t���O��TRUE�ɂ���Ǝ蓮��Uninit()�֐����Ăяo���K�v������
};

#endif
//*********************************************
//
// �I�u�W�F�N�g(object.cpp)
// Author : Junichi Uchiyama
//
//*********************************************

#include "object.h"
#include "renderer.h"
#include "application.h"

// �ÓI�����o�ϐ�
CObject* CObject::m_apObject[CObject::Priority::Max][MAX_OBJ] = {};
int CObject::m_nNumAll = 0;

/// <summary>
/// �R���X�g���N�^
/// </summary>
CObject::CObject(Priority priority) : m_priority(priority), m_ID(-1), m_objType(CObject::ObjType::DEFAULT)
{
	for (int i = 0; i < MAX_OBJ; i++)
	{
		if (m_apObject[priority][i] == nullptr)
		{
			m_apObject[priority][i] = this;	// ���g�̃|�C���^���i�[
			m_nNumAll++;
			m_ID = i;		// ���ʔԍ���ێ�
			break;
		}
	}

	assert(m_ID >= 0);

	m_pos = D3DXVECTOR3(0, 0, 0);
	m_rot = D3DXVECTOR3(0, 0, 0);
	m_scale = D3DXVECTOR3(1, 1, 1);		// �X�P�[���P
	m_color = 0xffffffff;

	// �X�V�������s�����ۂ�
	m_IsUpdate = true;
	// �蓮�ō폜���邩�ǂ���
	m_FlgManualRelease = false;

	m_StencilBufType = CStencil::STENCIL_TYPE::NONE;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CObject::~CObject()
{

}

/// <summary>
/// �f�o�b�O�`��
/// </summary>
void CObject::DebugDraw()
{
	//CApplication::GetInstance()->GetRenderer()->DebugDrawText();
}

/// <summary>
/// �S���
/// </summary>
void CObject::ReleaseAll()
{
	for (int priority = 0; priority < Priority::Max; priority++)
	{
		for (int i = 0; i < MAX_OBJ; i++)
		{
			if (m_apObject[priority][i] != nullptr && 
				m_apObject[priority][i]->m_FlgManualRelease == false)
			{
				m_apObject[priority][i]->Uninit();
			}
		}
	}
}

/// <summary>
/// �S�X�V
/// </summary>
void CObject::UpdateAll()
{
	for (int priority = 0; priority < Priority::Max; priority++)
	{
		for (int i = 0; i < MAX_OBJ; i++)
		{
			if (m_apObject[priority][i] != nullptr && m_apObject[priority][i]->m_IsUpdate)
			{
				m_apObject[priority][i]->Update();
			}
		}
	}
}

/// <summary>
/// �S�`��
/// </summary>
void CObject::DrawAll()
{
	for (int priority = 0; priority < Priority::Max; priority++)
	{
		for (int i = 0; i < MAX_OBJ; i++)
		{
			if (m_apObject[priority][i] != nullptr)
			{
				// �X�e���V���`��̓`�F�b�N���Ă���
				CStencil::STENCIL_TYPE type = m_apObject[priority][i]->GetStencilType();
				if (type >= CStencil::STENCIL_TYPE::BASE)
				{
					CStencil::Begine(type);
				}

				// �`��
				m_apObject[priority][i]->Draw();

				// �X�e���V���I��
				CStencil::End();

				// �d�Ȃ�I�u�W�F�N�g�̏ꍇ�͂�����x
				if (type == CStencil::STENCIL_TYPE::OVERLAP)
				{
					m_apObject[priority][i]->Draw();
				}
			}
		}
	}
}

void CObject::DrawDebugAll()
{
#ifndef _DEUBG

	for (int priority = 0; priority < Priority::Max; priority++)
	{
		for (int i = 0; i < MAX_OBJ; i++)
		{
			if (m_apObject[priority][i] != nullptr)
			{
				// �`��
				m_apObject[priority][i]->DebugDraw();
			}
		}
	}

#endif
}

/// <summary>
/// �I�u�W�F�N�g�^�C�v���擾
/// </summary>
/// <returns></returns>
CObject::ObjType CObject::GetObjType() const
{
	return m_objType;
}

/// <summary>
/// �I�u�W�F�N�g�^�C�v��ݒ�
/// </summary>
/// <param name="type"></param>
void CObject::SetObjType(CObject::ObjType type)
{
	m_objType = type;
}

/// <summary>
/// �I�u�W�F�N�g�擾
/// </summary>
/// <param name="type"></param>
/// <returns></returns>
CObject* CObject::GetObj(Priority priority, int idx)
{
	if (idx >= MAX_OBJ)
	{
		return nullptr;
	}

	return m_apObject[priority][idx];
}

/// <summary>
/// ���g�����
/// </summary>
void CObject::Release()
{
	int id = m_ID;		// ID��ێ�
	int priority = m_priority;

	delete m_apObject[priority][id];
	m_apObject[priority][id] = nullptr;

	m_nNumAll--;
}

/// <summary>
/// ���W�擾
/// </summary>
/// <returns></returns>
const D3DXVECTOR3& CObject::GetPos() const
{
	return m_pos;
}

/// <summary>
/// ���W�ݒ�i��_��POSTYPE�Őݒ�j
/// </summary>
/// <param name="pos"></param>
void CObject::SetPos(const D3DXVECTOR3& pos)
{
	m_pos = pos;
}

/// <summary>
/// ��]�擾
/// </summary>
/// <returns></returns>
const D3DXVECTOR3& CObject::GetRot() const
{
	return m_rot;
}

/// <summary>
/// ��]�ݒ�
/// </summary>
/// <param name="pos"></param>
void CObject::SetRot(const D3DXVECTOR3& rot)
{
	m_rot = rot;
}

/// <summary>
/// �X�P�[���擾
/// </summary>
/// <returns></returns>
const D3DXVECTOR3& CObject::GetScale() const
{
	return m_scale;
}

/// <summary>
/// �X�P�[���ݒ�
/// </summary>
/// <param name="pos"></param>
void CObject::SetScale(const D3DXVECTOR3& scale)
{
	m_scale = scale;
}

/// <summary>
/// �X�V���邩�擾
/// </summary>
/// <returns></returns>
bool CObject::IsUpdate()
{
	return m_IsUpdate;
}

/// <summary>
/// �X�V���邩�ݒ�
/// </summary>
/// <param name="flg"></param>
void CObject::SetIsUpdate(bool flg)
{
	m_IsUpdate = flg;
}

/// <summary>
/// �X�e���V���擾
/// </summary>
/// <returns></returns>
CStencil::STENCIL_TYPE CObject::GetStencilType()
{
	return m_StencilBufType;
}

/// <summary>
/// �X�e���V���ݒ�
/// </summary>
/// <param name="type"></param>
void CObject::SetStencilType(CStencil::STENCIL_TYPE type)
{
	m_StencilBufType = type;
}

/// <summary>
/// �J���[�擾
/// </summary>
/// <returns></returns>
const D3DXCOLOR& CObject::GetColor() const
{
	return m_color;
}

/// <summary>
/// �J���[�ݒ�
/// </summary>
/// <param name="col"></param>
void CObject::SetColor(const D3DXCOLOR& col)
{
	m_color = col;
}

/// <summary>
/// ID�擾
/// </summary>
/// <returns></returns>
int CObject::GetId()
{
	return m_ID;
}

/// <summary>
/// �蓮�ł̍폜�����邩
/// </summary>
/// <param name="manual"></param>
void CObject::SetFlgManualDelete(bool manual)
{
	m_FlgManualRelease = manual;
}
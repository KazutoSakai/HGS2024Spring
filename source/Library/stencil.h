//*********************************************
//
// �X�e���V���o�b�t�@(stencil.h)
// Author : Junichi Uchiyama
//
//*********************************************

#ifndef _STENCIL_H_
#define _STENCIL_H_

/// <summary>
/// �X�e���V���o�b�t�@�ł̌^�����`����Ǘ�
/// </summary>
class CStencil
{
public:
	
	//---------------------
	// enum

	// �X�e���V���o�b�t�@�̌^�������@��ς���
	enum STENCIL_TYPE
	{
		NONE = -1,
		BASE,			// �^������
		OVERLAP,		// �d�˂�I�u�W�F�N�g
		COLORPOLYGON,	// �F�|���S��

		MAX
	};

	//---------------------
	// public Method
	static void Begine(STENCIL_TYPE type);
	static void End();
};

#endif
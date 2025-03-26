//*********************************************
//
// �`��N���X(renderer.h)
// Author : Junichi Uchiyama
//
//*********************************************

#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "main.h"

/// <summary>
/// �����_���[�N���X
/// </summary>
class CRenderer
{
public:
	//---------------------
	// enum

	// �`��ݒ�
	enum RENDER_STATE
	{
		DEFAULT,		// �ʏ�
		ADD,			// ���Z����

		MAX,
	};

	//---------------------
	// public Method
	CRenderer();		// �R���X�g���N�^
	~CRenderer();		// �f�X�g���N�^

	HRESULT Init(HWND hWnd, BOOL bWindow);		// ������
	void Uninit();		// �j��
	void Update();		// �X�V
	void Draw();		// �`��

	LPDIRECT3DDEVICE9 GetDevice();				// �f�o�C�X�̎擾
	void SetRenderState(RENDER_STATE state);	// �`��ݒ�

	static void DebugDrawText(char* text);

private:
	//---------------------
	// private Method
	void DrawFPS();		// FPS�`��

	//---------------------
	// private Member
	LPDIRECT3D9 m_pD3D;					// Direct3D�I�u�W�F�N�g�ւ̃|�C���^
	LPDIRECT3DDEVICE9 m_pD3DDevice;		// Direct3D�f�o�C�X�ւ̃|�C���^

	//---------------------
	// static Member
	static const DWORD RENDER_COL = 0xff000000;
	static LPD3DXFONT m_pFont;			// �t�H���g�ւ̃|�C���^
	static int m_debugTextPos;
};

#endif
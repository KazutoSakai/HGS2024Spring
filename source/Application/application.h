//*********************************************
//
// �A�v���P�[�V����(application.h)
// Author : Junichi Uchiyama
//
//*********************************************

#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "main.h"

#include "renderer.h"
#include "input.h"
#include "sound.h"
#include "view.h"
#include "texture.h"
#include "light.h"
#include "SceneManager.h"

/// <summary>
/// �A�v���P�[�V��������ɕK�v�ȗv�f���Ǘ�
/// </summary>
class CApplication
{
public:

	//---------------------
	// �萔
	static const int SCREEN_SIDE_WIDTH = 256;
	static const int SCREEN_GAME_WIDTH = SCREEN_WIDTH - SCREEN_SIDE_WIDTH - SCREEN_SIDE_WIDTH;
	static const int SCREEN_CENTER_X = SCREEN_WIDTH / 2;
	static const int SCREEN_CENTER_Y = SCREEN_HEIGHT / 2;
	//---------------------
	// Singleton
	static CApplication* GetInstance()
	{
		static CApplication instance;
		return &instance;
	}
	CApplication(const CApplication&) = delete;
	CApplication& operator=(const CApplication&) = delete;
	CApplication(CApplication&&) = delete;
	CApplication& operator=(CApplication&&) = delete;

	//---------------------
	// Method
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);		// ������
	void Uninit();						// ���
	void Update();						// �X�V
	void Draw();						// �`��

	//---------------------
	// Getter
	CRenderer* GetRenderer() { return m_pRenderer; }
	CInputManager* GetInput() { return m_pInputManager; }
	CInputMouse* GetMouse() { return m_pInputMouse; }
	CSound* GetSound() { return m_pSound; }
	CView* GetView() { return m_pView; }
	CTexture* GetTexture() { return m_pTexture; }
	CLight* GetLight() { return m_pLight; }

	CSceneManager* GetScene() { return m_pSceneManager; }

#ifdef _DEBUG
	void DebugUpdateCamera();
	void DebugDraw();
	bool GetDebugCamera() { return m_IsDebugCamera; }
#endif

private:
	//---------------------
	// default
	CApplication();						// �R���X�g���N�^
	~CApplication();					// �f�X�g���N�^

	//---------------------
	// Member
	bool m_bPause;						// �|�[�Y�����ǂ���

	//---------------------
	// library
	CRenderer* m_pRenderer;				// �I�u�W�F�N�g�`��
	CInputManager* m_pInputManager;	// �L�[�{�[�h����
	CInputMouse* m_pInputMouse;			// �}�E�X����
	CSound* m_pSound;					// �T�E���h
	CView* m_pView;						// �r���[(�J����)
	CTexture* m_pTexture;				// �e�N�X�`���Ǘ�
	CLight* m_pLight;					// ���C�g�Ǘ�

	//---------------------
	// Application
	CSceneManager* m_pSceneManager;		// �V�[���J�ڊǗ�

#ifdef _DEBUG
	bool m_IsDebugCamera;				// �J�����̃f�o�b�O�؂�ւ�
#endif
};

#endif
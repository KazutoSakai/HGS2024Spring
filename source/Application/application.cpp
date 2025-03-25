//*********************************************
//
// �A�v���P�[�V����(application.cpp)
// Author : Junichi Uchiyama
//
//*********************************************

#include "application.h"

#include "light.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
CApplication::CApplication()
{
	m_pRenderer = nullptr;
	m_pInputManager = nullptr;
	m_pInputMouse = nullptr;
	m_pSound = nullptr;
	m_pView = nullptr;
	m_pSceneManager = nullptr;
	m_pTexture = nullptr;

	m_bPause = false;

#ifdef _DEBUG
	m_IsDebugCamera = false;
#endif
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CApplication::~CApplication()
{

}

/// <summary>
/// ������
/// </summary>
/// <param name="hWnd"></param>
/// <param name="bWindow"></param>
/// <returns></returns>
HRESULT CApplication::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// �����_���[
	m_pRenderer = DBG_NEW CRenderer();
	m_pRenderer->Init(hWnd, bWindow);

	// �L�[�{�[�h
	m_pInputManager = DBG_NEW CInputManager();
	m_pInputManager->Init(hInstance, hWnd);

	// �}�E�X
	m_pInputMouse = DBG_NEW CInputMouse();
	m_pInputMouse->Init(hInstance, hWnd);

	// �T�E���h
	m_pSound = DBG_NEW CSound();
	m_pSound->Init(hWnd);

	// �r���[
	m_pView = CView::Create();
	m_pView->SetFlgManualDelete(true);

	// �e�N�X�`��
	m_pTexture = DBG_NEW CTexture();

	// ���C�g������
	m_pLight = DBG_NEW CLight();
	m_pLight->Init();

	// �V�[���Ǎ�
	m_pSceneManager = DBG_NEW CSceneManager();
	m_pSceneManager->Init();

	return S_OK;
}

/// <summary>
/// ���
/// </summary>
void CApplication::Uninit()
{
	// �S���
	CObject::ReleaseAll();

	// �蓮���
	if (m_pView != nullptr)
		m_pView->Uninit();

	if (m_pTexture != nullptr)
	{
		m_pTexture->ReleaseAll();
		delete m_pTexture;
		m_pTexture = nullptr;
	}

	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	if (m_pInputManager != nullptr)
	{
		m_pInputManager->Uninit();
		delete m_pInputManager;
		m_pInputManager = nullptr;
	}

	if (m_pInputMouse != nullptr)
	{
		m_pInputMouse->Uninit();
		delete m_pInputMouse;
		m_pInputMouse = nullptr;
	}

	if (m_pSound != nullptr)
	{
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = nullptr;
	}

	if (m_pLight != nullptr)
	{
		delete m_pLight;
	}

	if (m_pSceneManager)
	{
		m_pSceneManager->Uninit();
		delete m_pSceneManager;
		m_pSceneManager = nullptr;
	}
}

/// <summary>
/// �X�V
/// </summary>
void CApplication::Update()
{
	// �L�[�{�[�h���͍X�V
	if (m_pInputManager != nullptr)
	{
		m_pInputManager->Update();

#ifdef _DEBUG
		// �J�����f�o�b�O���삪�\
		DebugUpdateCamera();
#endif

	}

	// �}�E�X���͍X�V
	if (m_pInputMouse != nullptr)
		m_pInputMouse->Update();

	// �|�[�Y���͈ȉ��̏��������s���Ȃ�
	if (m_bPause)
		return;

	// �e�V�[�����Ƃ̍X�V����
	if (m_pSceneManager != nullptr)
		m_pSceneManager->Update();

	// �I�u�W�F�N�g�̍X�V
	if (m_pRenderer != nullptr)
		m_pRenderer->Update();
}

/// <summary>
/// �`��
/// </summary>
void CApplication::Draw()
{
	// �e�V�[�����Ƃ̕`��
	if(m_pSceneManager != nullptr)
		m_pSceneManager->Draw();

	// �I�u�W�F�N�g�̕`��
	if (m_pRenderer != nullptr)
		m_pRenderer->Draw();
}

#ifdef _DEBUG

void CApplication::DebugUpdateCamera()
{

	// �f�o�b�O
	if (m_pInputManager->GetTrigger(CInputManager::InputType::StartPause))
	{
		m_bPause = !m_bPause;
	}
	else if (m_pInputManager->GetKeyboard()->GetTrigger(DIK_F2))
	{
		m_IsDebugCamera = (!m_IsDebugCamera);
	}
}

void CApplication::DebugDraw()
{
#ifdef _DEBUG
	char text[256];
	sprintf(&text[0], "�J�����f�o�b�O�ؑցFF2");
	m_pRenderer->DebugDrawText(text);
#endif
}

#endif
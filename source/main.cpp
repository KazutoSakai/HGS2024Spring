//*********************************************
//
// C++�Q�[������(main.cpp)
// Author : Junichi Uchiyama
//
//*********************************************

// �t�@�C���ǂݍ���
#include "main.h"
#include "application.h"

// �v���g�^�C�v�錾
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
bool OutputFinishedMessageBox(HWND hWnd);

// �O���[�o���ϐ�
int g_nCountFPS = 0;			// FPS�J�E���^�[
float g_fDeltaSecond = 0.0f;	// Delta�^�C��

/// <summary>
/// ���C���֐�
/// </summary>
/// <param name="hInstance">���̃A�v���P�[�V�����̃C���X�^���X�n���h���i���ʎq�j</param>
/// <param name="hInstancePrev">���NULL</param>
/// <param name="lpCmdLine">�R�}���h���C���Ŏ󂯎���������ւ̃|�C���^</param>
/// <param name="nCmdShow">�����E�B���h�E�̕\�����@</param>
/// <returns></returns>
int WINAPI WinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hInstancePrev,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow)
{
	//_CrtSetBreakAlloc(1061);

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),					// WNDCLASSEX�̃������T�C�Y
		CS_CLASSDC,							// �E�B���h�E�̃X�^�C��
		WindowProc,							// �E�B���h�E�v���V�[�W��
		0,									// �O�ɂ���i�ʏ�͂��Ȃ��j
		0,									// �O�ɂ���i�ʏ�͂��Ȃ��j
		hInstance,							// �C���X�^���X�n���h��
		LoadIcon(NULL, IDI_APPLICATION),	// �^�X�N�o�[�̃A�C�R��
		LoadCursor(NULL, IDC_ARROW),		// �}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1),			// �N���C�A���g�̈�̔w�i�F
		NULL,								// ���j���[�o�[
		CLASS_NAME,							// �E�B���h�E�N���X�̖��O
		LoadIcon(NULL, IDI_APPLICATION)		// �t�@�C���̃A�C�R��
	};

	HWND hWnd;					// �E�B���h�E�n���h���i���ʎq�j
	MSG msg;					// ���b�Z�[�W���i�[����ϐ�
	RECT rect = { 0,0,SCREEN_WIDTH, SCREEN_HEIGHT };	// ��ʃT�C�Y�̍\����
	DWORD dwCurrentTime;		// ���ݎ���
	DWORD dwExecLastTime;		// �Ō�ɏ�����������
	DWORD dwFrameCount;			// �t���[���J�E���g
	DWORD dwFPSLastTime;		// �Ō��FPS���v����������

	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �N���C�A���g�V����w��̃T�C�Y�ɒ���
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	// �E�B���h�E�𐶐�
	hWnd = CreateWindowEx(0,		// �g���E�B���h�E�X�^�C��
		CLASS_NAME,					// �E�B���h�E�N���X�̖��O
		WINDOW_NAME,				// �E�B���h�E�̖��O
		WS_OVERLAPPEDWINDOW,		// �E�B���h�E�X�^�C��
		CW_USEDEFAULT,				// �E�B���h�E�̍��゘���W
		CW_USEDEFAULT,				// �E�B���h�E�̍��゙���W
		(rect.right - rect.left),	// �E�B���h�E�̕�
		(rect.bottom - rect.top),	// �E�B���h�E�̍���
		NULL,						// �e�E�B���h�E�̃n���h��
		NULL,						// ���j���[�n���h���܂��͎q�E�B���h�EID
		hInstance,					// �E�B���h�E�쐬�f�[�^
		NULL);

	// ����������
	CApplication* pApp = CApplication::GetInstance();
	pApp->Init(hInstance, hWnd, TRUE);

	// ����\��ݒ�
	timeBeginPeriod(1);
	dwCurrentTime = 0;					// ����������
	dwExecLastTime = timeGetTime();		// ���ݎ������擾�i�ۑ��j
	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();

	// �E�B���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);			// �E�B���h�E�̕\����Ԃ�ݒ�
	UpdateWindow(hWnd);					// �N���C�A���g�̈���X�V

	// ���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{// Windows�̏���
			if (msg.message == WM_QUIT)
			{// WM_QUIT���b�Z�[�W���󂯎�����烁�b�Z�[�W���[�v�𔲂���
				break;
			}
			else
			{
				// ���b�Z�[�W�̐ݒ�
				TranslateMessage(&msg);			// ���z�L�[���b�Z�[�W�𕶎����b�Z�[�W�֕ϊ�
				DispatchMessage(&msg);			// �E�B���h�E�v���V�[�W���փ��b�Z�[�W�𑗏o
			}
		}
		else
		{// DirectX�̏���
			dwCurrentTime = timeGetTime();		// ���ݎ������擾
			
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{// 0.5�b�o��
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;		// FPS�𑪒肵��������ۑ�
				dwFrameCount = 0;					// �t���[���J�E���g���N���A
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{// 60����1�b�o��

				g_fDeltaSecond = (float)(dwCurrentTime - dwExecLastTime);

				dwExecLastTime = dwCurrentTime;		// �����J�n�̎����i���ݎ����j��ۑ�

				// �X�V
				pApp->Update();

				// �`��
				pApp->Draw();

				// �t���[���J�E���g�����Z
				dwFrameCount++;
			}
		}
	}

	// �I������
	if (pApp != nullptr)
	{
		pApp->Uninit();
	}

	// ����\��߂�
	timeEndPeriod(1);

	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// ���������[�N���o
	_CrtDumpMemoryLeaks();

	return (int)msg.wParam;
}

/// <summary>
/// �E�B���h�E�v���V�[�W��
/// </summary>
/// <param name="hWnd">�E�B���h�E�n���h���i���ʎq�j</param>
/// <param name="uMsg">���b�Z�[�W</param>
/// <param name="wParam">�p�����[�^���̂P</param>
/// <param name="lParam">�p�����[�^���̂Q</param>
/// <returns></returns>
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	bool result = false;

	switch (uMsg)
	{
	case WM_DESTROY:		// �E�B���h�E�j�����b�Z�[�W
		// WM_QUIT���b�Z�[�W�𑗂�
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:		// �L�[�����̃��b�Z�[�W
		switch (wParam)
		{
		case VK_ESCAPE:		// ESC�L�[�������ꂽ
			// �E�B���h�E��j������iWM_DESTROY���b�Z�[�W�𑗂�j
			result = OutputFinishedMessageBox(hWnd);
			if (result == true)
			{
				// �E�B���h�E��j������
				DestroyWindow(hWnd);
			}
			break;
		}
		break;
	case WM_CLOSE:			// ����{�^�������̃��b�Z�[�W
		result = OutputFinishedMessageBox(hWnd);
		if (result == true)
		{
			// �E�B���h�E��j������
			DestroyWindow(hWnd);
		}
		else
		{
			return 0;		// WM_CLOSE���b�Z�[�W�̕Ԏ���0��Ԃ��Ȃ��ƏI�����Ă��܂�
		}
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

/// <summary>
/// �I�����b�Z�[�WBOX
/// </summary>
/// <param name="hWnd"></param>
/// <returns>true�F�I���Afalse�F�I�����Ȃ�</returns>
bool OutputFinishedMessageBox(HWND hWnd)
{
	int nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO | MB_ICONQUESTION);

	return (nID == IDYES) ? true : false;
}


/// <summary>
/// FPS�J�E���^�[�擾
/// </summary>
/// <returns></returns>
int GetFPS()
{
	return g_nCountFPS;
}

/// <summary>
/// �t���[���Ԃ̕b��
/// </summary>
/// <returns></returns>
float GetWorldDeltaSeconds()
{
	return g_fDeltaSecond * 0.001f;
}
//*********************************************
//
// ���͏���(input.cpp)
// Author : Junichi Uchiyama
//
//*********************************************

#include "input.h"
#include "application.h"

//------------------------------------
// class CInput
//------------------------------------

// �ÓI�����o�ϐ�
LPDIRECTINPUT8 CInput::m_pInput = nullptr;

/// <summary>
/// �R���X�g���N�^
/// </summary>
CInput::CInput() : m_pDevice(nullptr)
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CInput::~CInput()
{

}

/// <summary>
/// ������
/// </summary>
/// <param name="hWnd"></param>
/// <param name="bWindow"></param>
/// <returns></returns>
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	HRESULT hr = S_FALSE;

	// DirectInput�I�u�W�F�N�g�̐���
	if (m_pInput == nullptr)
	{
		hr = DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
			IID_IDirectInput8, (void**)&m_pInput, NULL);
	}

	return S_OK;
}

/// <summary>
/// ���
/// </summary>
void CInput::Uninit()
{
	if (m_pInput != nullptr)
	{
		m_pInput->Release();
		m_pInput = nullptr;
	}

	if (m_pDevice != nullptr)
	{
		m_pDevice->Unacquire();

		m_pDevice->Release();
		m_pDevice = nullptr;
	}
}

//------------------------------------
// class CInputKeyboard
//------------------------------------

/// <summary>
/// �R���X�g���N�^
/// </summary>
CInputKeyboard::CInputKeyboard()
{
	memset(&m_aKeyState, 0, sizeof(m_aKeyState));
	memset(&m_aKeyStateTrigger, 0, sizeof(m_aKeyStateTrigger));
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CInputKeyboard::~CInputKeyboard()
{

}

/// <summary>
/// ������
/// </summary>
/// <param name="hWnd"></param>
/// <param name="bWindow"></param>
/// <returns></returns>
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (FAILED(CInput::Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	// ���̓f�o�C�X�i�L�[�{�[�h�j�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g�̐ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// �������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��
	m_pDevice->Acquire();

	return S_OK;
}

/// <summary>
/// ���
/// </summary>
void CInputKeyboard::Uninit()
{
	CInput::Uninit();
}

/// <summary>
/// �X�V
/// </summary>
void CInputKeyboard::Update()
{
	BYTE aKeyState[MAX_KEY];	// �L�[�{�[�h�̓��͏��
	int nCntKey;

	// ���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < MAX_KEY; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];		// �L�[�{�[�h��Trigger����ۑ�
			m_aKeyStateRelease[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & m_aKeyState[nCntKey];	// �L�[�{�[�h��Release����ۑ�
			m_aKeyState[nCntKey] = aKeyState[nCntKey];		// �L�[�{�[�h��Press����ۑ�
		}
	}
	else
	{
		m_pDevice->Acquire();		// �L�[�{�[�h�ւ̃A�N�Z�X�����l��
	}
}

/// <summary>
/// �����Ă��鎞
/// </summary>
/// <param name="nKey"></param>
/// <returns></returns>
bool CInputKeyboard::GetPress(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) ? true : false;
}

/// <summary>
/// ��������
/// </summary>
/// <param name="nKey"></param>
/// <returns></returns>
bool CInputKeyboard::GetTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

/// <summary>
/// ��������
/// </summary>
/// <param name="nKey"></param>
/// <returns></returns>
bool CInputKeyboard::GetRelease(int nKey)
{
	return (m_aKeyStateRelease[nKey] & 0x80) && !(m_aKeyState[nKey] & 0x80);
}

/// <summary>
/// �J��Ԃ������i�������j
/// </summary>
/// <param name="nKey"></param>
/// <returns></returns>
bool CInputKeyboard::GetRepeat(int nKey)
{
	return false;
}

//------------------------------------
// class CInputMouse
//------------------------------------

/// <summary>
/// �R���X�g���N�^
/// </summary>
CInputMouse::CInputMouse() : m_dims({})
{
	for (int i = 0; i < (int)MouseButtonType::Max; i++)
	{
		m_CurrentDistance = D3DXVECTOR3(0, 0, 0);
		m_IsDragArray[i] = false;
	}

	m_hWnd = nullptr;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CInputMouse::~CInputMouse()
{

}

/// <summary>
/// ������
/// </summary>
/// <param name="hInstance"></param>
/// <param name="hWnd"></param>
/// <returns></returns>
HRESULT CInputMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	// �ێ����Ă���
	m_hWnd = hWnd;

	if (FAILED(CInput::Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	// ���̓f�o�C�X�i�L�[�{�[�h�j�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g�̐ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIMouse)))
	{
		return E_FAIL;
	}

	// �������[�h��ݒ�
	//if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_NONEXCLUSIVE | DISCL_FOREGROUND))))
	{
		return E_FAIL;
	}

	// �}�E�X�v���p�e�B�̐ݒ�
	DIPROPDWORD dipdw;
	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = DIPROPAXISMODE_REL; // ���΍��W���[�h
	//dipdw.dwData = DIPROPAXISMODE_ABS; // ��΍��W���[�h
	if (FAILED(m_pDevice->SetProperty(DIPROP_AXISMODE, &dipdw.diph)))
	{
		return E_FAIL;
	}

	// �ڑ�
	m_pDevice->Acquire();

	return S_OK;
}

/// <summary>
/// ���
/// </summary>
void CInputMouse::Uninit()
{
	CInput::Uninit();
}

/// <summary>
/// �X�V
/// </summary>
void CInputMouse::Update()
{
	// �E�B���h�E���A�N�e�B�u���ǂ���
	HWND hWnd = GetActiveWindow();
	bool isWindowActive = false;
	//if (m_hWnd != hWnd) return;		// �A�N�e�B�u�łȂ��Ȃ�X�L�b�v

	//DIMOUSESTATE dims;
	HRESULT hr = m_pDevice->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&m_dims);
	if(SUCCEEDED(hr))
	{
		// �}�E�X�h���b�O����
		for (int i = 0; i < (int)MouseButtonType::Max; i++)
		{
			// �N���b�N���o
			if ((m_dims.rgbButtons[i] & 128) && m_IsDragArray[i] == false)
			{
				m_IsDragArray[i] = true;
			}
			else if (!(m_dims.rgbButtons[i] & 128))
			{
				// ���Z�b�g
				m_IsDragArray[i] = false;
			}
		}
		// �}�E�X�ړ������ێ�
		m_CurrentDistance.x = (float)m_dims.lX;		// X��
		m_CurrentDistance.y = (float)m_dims.lY;		// Y��
		m_CurrentDistance.z = (float)m_dims.lZ;		// �z�C�[��
	}
	else
	{
		m_pDevice->Unacquire();

		hr = m_pDevice->Acquire();
	}

#if 0

	//// �}�E�X����
	//for (int i = 0; i < (int)MouseButtonType::Max; i++)
	//{
	//	// �N���b�N���o
	//	MouseInfo* info = &m_MouseInfo[i];
	//	if (GetAsyncKeyState((int)MouseButtonType::L_Button + i) & 0x8000 && info->m_IsDrag == false)
	//	{
	//		info->m_IsDrag = true;
	//		GetCursorPos(&info->m_MousePosStart);
	//	}
	//	else if (!(GetAsyncKeyState((int)MouseButtonType::L_Button + i) & 0x8000))
	//	{
	//		// ���Z�b�g
	//		info->m_IsDrag = false;
	//		info->m_CurrentDistance = D3DXVECTOR3(0, 0, 0);
	//	}

	//	// �h���b�O����
	//	if (info->m_IsDrag)
	//	{
	//		// �h���b�O��̌��݂̍��W
	//		GetCursorPos(&info->m_MousePosCurrent);


	//		// ���������߂�
	//		info->m_CurrentDistance.x = (float)(info->m_MousePosCurrent.x - info->m_MousePosStart.x);
	//		info->m_CurrentDistance.y = (float)(info->m_MousePosCurrent.y - info->m_MousePosStart.y);

	//		// �v�Z��V�������W���n�_�Ƃ���
	//		GetCursorPos(&info->m_MousePosStart);
	//	}
	//}

#endif
}

/// <summary>
/// �h���b�O���Ă��邩
/// </summary>
/// <param name="type"></param>
/// <returns></returns>
bool CInputMouse::IsMouseButtonDrag(MouseButtonType type)
{
	return m_IsDragArray[(int)type];
}

/// <summary>
/// �}�E�X���擾
/// </summary>
/// <param name="type"></param>
/// <returns></returns>
D3DXVECTOR3& CInputMouse::GetMouseMoveDist()
{
	return m_CurrentDistance;
}

void CInputMouse::DebugDraw()
{
#ifdef _DEBUG
	char text[256];
	CRenderer* pRender = CApplication::GetInstance()->GetRenderer();

	sprintf(&text[0], "Mouse.dims[[0]: %d , [1]: %d , [2]: %d , [3]: %d , lX: %d , lY: %d, lZ: %d]", m_dims.rgbButtons[0], m_dims.rgbButtons[1], m_dims.rgbButtons[2], m_dims.rgbButtons[3], m_dims.lX, m_dims.lY, m_dims.lZ);
	pRender->DebugDrawText(text);
#endif
}


//------------------------------------
// class CInputPad
//------------------------------------

// static
int CInputPad::m_padNumAll = 0;

CInputPad::CInputPad()
{
	// �[���N���A
	memset(&m_joyKeyState, 0, sizeof(XINPUT_STATE));
	memset(&m_joyKeyTrigger, 0, sizeof(XINPUT_STATE));
	memset(&m_joyKeyRelease, 0, sizeof(XINPUT_STATE));
	memset(&m_vibration, 0, sizeof(XINPUT_VIBRATION));
}

CInputPad::~CInputPad()
{

}

/// <summary>
/// �����ݒ�
/// </summary>
/// <returns></returns>
HRESULT CInputPad::Init()
{
	// �ŏ��̂ЂƂ����ŗL��
	if(m_padNumAll == 0)
		XInputEnable(true);

	m_padID = m_padNumAll++;

	return S_OK;
}

/// <summary>
/// ����iXInpu�������j
/// </summary>
void CInputPad::Uninit()
{
	m_padNumAll--;

	// �Ō�̂ЂƂŖ���
	if(m_padNumAll == 0)
		XInputEnable(false);
}

/// <summary>
/// �p�b�h��Press��ԍX�V
/// </summary>
void CInputPad::Update()
{
	XINPUT_STATE pressState;

	// XInput�̓��͏�Ԃ��擾
	if (XInputGetState(m_padID, &pressState) == ERROR_SUCCESS)
	{
		// Trigger
		m_joyKeyTrigger.Gamepad.wButtons = (m_joyKeyState.Gamepad.wButtons ^ pressState.Gamepad.wButtons) & pressState.Gamepad.wButtons;
		// Release
		m_joyKeyRelease.Gamepad.wButtons = (m_joyKeyState.Gamepad.wButtons ^ pressState.Gamepad.wButtons) & ~pressState.Gamepad.wButtons;
		// Press
		m_joyKeyState = pressState;
	}
}

/// <summary>
/// �����Ă���
/// </summary>
/// <param name="nKey"></param>
/// <returns></returns>
bool CInputPad::GetPress(InputButton btn)
{
	int nKey = (int)btn;
	return (m_joyKeyState.Gamepad.wButtons & (0x01 << nKey)) ? true : false;
}

/// <summary>
/// �������u��
/// </summary>
/// <param name="btn"></param>
/// <returns></returns>
bool CInputPad::GetTrigger(InputButton btn)
{
	int nKey = (int)btn;
	return (m_joyKeyTrigger.Gamepad.wButtons & (0x01 << nKey)) ? true : false;
}

/// <summary>
/// �������u��
/// </summary>
/// <param name="btn"></param>
/// <returns></returns>
bool CInputPad::GetRelease(InputButton btn)
{
	int nKey = (int)btn;
	return (m_joyKeyRelease.Gamepad.wButtons & (0x01 << nKey)) ? true : false;
}

/// <summary>
/// ���s�[�g�����i�������j
/// </summary>
/// <param name="btn"></param>
/// <returns></returns>
bool CInputPad::GetRepeat(InputButton btn)
{
	return false;
}

/// <summary>
/// ���X�e�B�b�N�̌X��
/// </summary>
/// <param name="pOutDir"></param>
/// <returns></returns>
bool CInputPad::GetLeftStickDir(D3DXVECTOR2* pOutDir)
{
	SHORT lx = m_joyKeyState.Gamepad.sThumbLX;
	SHORT ly = m_joyKeyState.Gamepad.sThumbLY;

	// �X���̒l���擾
	if (pOutDir)
	{
		pOutDir->x = GetNormalizedThumb(lx);
		pOutDir->y = GetNormalizedThumb(ly);
	}

	// �X���̗V��
	if (lx > 80 || lx < -80
		|| ly > 80 || ly < -80)
	{
		return true;
	}

	return false;
}

/// <summary>
/// �E�X�e�B�b�N�̌X��
/// </summary>
/// <param name="pOutDir"></param>
/// <returns></returns>
bool CInputPad::GetRightStickDir(D3DXVECTOR2* pOutDir)
{
	SHORT rx = m_joyKeyState.Gamepad.sThumbRX;
	SHORT ry = m_joyKeyState.Gamepad.sThumbRY;

	// �X���̒l���擾
	if (pOutDir)
	{
		pOutDir->x = GetNormalizedThumb(rx);
		pOutDir->y = GetNormalizedThumb(ry);
	}

	// �X���̗V��
	if (rx > 80 || rx < -80
		|| ry > 80 || ry < -80)
	{
		return true;
	}

	return false;
}

/// <summary>
/// �X�e�B�b�N�̌X���l�i-32768�`32767�j�𐳋K��
/// </summary>
/// <param name="sThumb"></param>
/// <returns></returns>
float CInputPad::GetNormalizedThumb(SHORT sThumb)
{
	return (sThumb >= 0) ? sThumb / 32767.f : sThumb / 32768.f;
}

/// <summary>
/// �o�C�u���[�V�����ݒ�
/// </summary>
void CInputPad::SetVibrationEnable(bool enable)
{
	int value = (enable == true) ? 65535 : 0;

	m_vibration.wLeftMotorSpeed = value;
	m_vibration.wRightMotorSpeed = value;

	// �R���g���[���[�̏�Ԃ�ݒ肷��
	XInputSetState(m_padID, &m_vibration);
}

//------------------------------------
// class CInputManager
//------------------------------------
CInputManager::CInputManager()
{
	m_pKeyboard = nullptr;
	m_pPad = nullptr;
}

CInputManager::~CInputManager()
{
	if (m_pKeyboard != nullptr)
		delete m_pKeyboard;

	if (m_pPad != nullptr)
		delete m_pPad;
}

/// <summary>
/// �����ݒ�
/// </summary>
/// <param name="hInstance"></param>
/// <param name="hWnd"></param>
/// <returns></returns>
HRESULT CInputManager::Init(HINSTANCE hInstance, HWND hWnd)
{
	m_pKeyboard = DBG_NEW CInputKeyboard();
	m_pKeyboard->Init(hInstance, hWnd);

	m_pPad = DBG_NEW CInputPad();
	m_pPad->Init();

	return S_OK;
}

/// <summary>
/// ���
/// </summary>
void CInputManager::Uninit()
{
	if (m_pKeyboard != nullptr)
	{
		delete m_pKeyboard;
		m_pKeyboard = nullptr;
	}

	if (m_pPad != nullptr)
	{
		delete m_pPad;
		m_pPad = nullptr;
	}
}

/// <summary>
/// �X�V����
/// </summary>
void CInputManager::Update()
{
	if (m_pKeyboard != nullptr)
		m_pKeyboard->Update();

	if (m_pPad != nullptr)
		m_pPad->Update();
}

/// <summary>
/// �����Ă���
/// </summary>
/// <param name="type"></param>
/// <returns></returns>
bool CInputManager::GetPress(InputType type)
{
	return m_pKeyboard->GetPress(ConvertToKeyboard(type)) ||
		m_pPad->GetPress(ConvertToPad(type)) ||
		GetPressMove(type);
}

/// <summary>
/// �������u��
/// </summary>
/// <param name="type"></param>
/// <returns></returns>
bool CInputManager::GetTrigger(InputType type)
{
	return m_pKeyboard->GetTrigger(ConvertToKeyboard(type)) || 
		m_pPad->GetTrigger(ConvertToPad(type));
}

/// <summary>
/// �������u��
/// </summary>
/// <param name="type"></param>
/// <returns></returns>
bool CInputManager::GetRelease(InputType type)
{
	return m_pKeyboard->GetRelease(ConvertToKeyboard(type)) ||
		m_pPad->GetRelease(ConvertToPad(type));
}

bool CInputManager::GetPressMove(InputType type)
{
	D3DXVECTOR2 padDir;
	if (!GetPad()->GetLeftStickDir(&padDir))
		return false;

	switch (type)
	{
	case CInputManager::InputType::Decide_A:
		break;
	case CInputManager::InputType::Cancel_B:
		break;
	case CInputManager::InputType::Action_X:
		break;
	case CInputManager::InputType::Action_Y:
		break;
	case CInputManager::InputType::Move_Up:
		return padDir.y > 0;
	case CInputManager::InputType::Move_Down:
		return padDir.y < 0;
	case CInputManager::InputType::Move_Left:
		return padDir.x < 0;
	case CInputManager::InputType::Move_Right:
		return padDir.x > 0;
	case CInputManager::InputType::StartPause:
		break;
	default:
		break;
	}

	return false;
}

/// <summary>
/// �L�[�{�[�h���͂֕ϊ�
/// </summary>
/// <param name="type"></param>
/// <returns></returns>
int CInputManager::ConvertToKeyboard(InputType type)
{
	switch (type)
	{
	case CInputManager::InputType::Decide_A:
		return DIK_RETURN;
	case CInputManager::InputType::Cancel_B:
		return DIK_BACKSPACE;
	case CInputManager::InputType::Action_X:
		return DIK_E;
	case CInputManager::InputType::Action_Y:
		return DIK_R;
	case CInputManager::InputType::Move_Up:
		return DIK_W;
	case CInputManager::InputType::Move_Down:
		return DIK_S;
	case CInputManager::InputType::Move_Left:
		return DIK_A;
	case CInputManager::InputType::Move_Right:
		return DIK_D;
	case CInputManager::InputType::StartPause:
		return DIK_P;
	default:
		assert(false);
		break;
	}

	return 0;
}

/// <summary>
/// �p�b�h���͂֕ϊ�
/// </summary>
/// <param name="type"></param>
/// <returns></returns>
CInputPad::InputButton CInputManager::ConvertToPad(InputType type)
{
	switch (type)
	{
	case CInputManager::InputType::Decide_A:
		return CInputPad::InputButton::Button_A;
	case CInputManager::InputType::Cancel_B:
		return CInputPad::InputButton::Button_B;
	case CInputManager::InputType::Action_X:
		return CInputPad::InputButton::Button_X;
	case CInputManager::InputType::Action_Y:
		return CInputPad::InputButton::Button_Y;
	case CInputManager::InputType::Move_Up:
		return CInputPad::InputButton::Button_Up;
	case CInputManager::InputType::Move_Down:
		return CInputPad::InputButton::Button_Down;
	case CInputManager::InputType::Move_Left:
		return CInputPad::InputButton::Button_Left;
	case CInputManager::InputType::Move_Right:
		return CInputPad::InputButton::Button_Right;
	case CInputManager::InputType::StartPause:
		return CInputPad::InputButton::Button_Start;
	default:
		assert(false);
		break;
	}

	return CInputPad::InputButton::Invalid;
}
//*********************************************
//
// 入力処理(input.cpp)
// Author : Junichi Uchiyama
//
//*********************************************

#include "input.h"
#include "application.h"

//------------------------------------
// class CInput
//------------------------------------

// 静的メンバ変数
LPDIRECTINPUT8 CInput::m_pInput = nullptr;

/// <summary>
/// コンストラクタ
/// </summary>
CInput::CInput() : m_pDevice(nullptr)
{

}

/// <summary>
/// デストラクタ
/// </summary>
CInput::~CInput()
{

}

/// <summary>
/// 初期化
/// </summary>
/// <param name="hWnd"></param>
/// <param name="bWindow"></param>
/// <returns></returns>
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	HRESULT hr = S_FALSE;

	// DirectInputオブジェクトの生成
	if (m_pInput == nullptr)
	{
		hr = DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
			IID_IDirectInput8, (void**)&m_pInput, NULL);
	}

	return S_OK;
}

/// <summary>
/// 解放
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
/// コンストラクタ
/// </summary>
CInputKeyboard::CInputKeyboard()
{
	memset(&m_aKeyState, 0, sizeof(m_aKeyState));
	memset(&m_aKeyStateTrigger, 0, sizeof(m_aKeyStateTrigger));
}

/// <summary>
/// デストラクタ
/// </summary>
CInputKeyboard::~CInputKeyboard()
{

}

/// <summary>
/// 初期化
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

	// 入力デバイス（キーボード）の生成
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	// データフォーマットの設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// 協調モードを設定
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// キーボードへのアクセス権を獲得
	m_pDevice->Acquire();

	return S_OK;
}

/// <summary>
/// 解放
/// </summary>
void CInputKeyboard::Uninit()
{
	CInput::Uninit();
}

/// <summary>
/// 更新
/// </summary>
void CInputKeyboard::Update()
{
	BYTE aKeyState[MAX_KEY];	// キーボードの入力情報
	int nCntKey;

	// 入力デバイスからデータを取得
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < MAX_KEY; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];		// キーボードのTrigger情報を保存
			m_aKeyStateRelease[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & m_aKeyState[nCntKey];	// キーボードのRelease情報を保存
			m_aKeyState[nCntKey] = aKeyState[nCntKey];		// キーボードのPress情報を保存
		}
	}
	else
	{
		m_pDevice->Acquire();		// キーボードへのアクセス権を獲得
	}
}

/// <summary>
/// 押している時
/// </summary>
/// <param name="nKey"></param>
/// <returns></returns>
bool CInputKeyboard::GetPress(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) ? true : false;
}

/// <summary>
/// 押した時
/// </summary>
/// <param name="nKey"></param>
/// <returns></returns>
bool CInputKeyboard::GetTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

/// <summary>
/// 離した時
/// </summary>
/// <param name="nKey"></param>
/// <returns></returns>
bool CInputKeyboard::GetRelease(int nKey)
{
	return (m_aKeyStateRelease[nKey] & 0x80) && !(m_aKeyState[nKey] & 0x80);
}

/// <summary>
/// 繰り返し処理（未実装）
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
/// コンストラクタ
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
/// デストラクタ
/// </summary>
CInputMouse::~CInputMouse()
{

}

/// <summary>
/// 初期化
/// </summary>
/// <param name="hInstance"></param>
/// <param name="hWnd"></param>
/// <returns></returns>
HRESULT CInputMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	// 保持しておく
	m_hWnd = hWnd;

	if (FAILED(CInput::Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	// 入力デバイス（キーボード）の生成
	if (FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	// データフォーマットの設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIMouse)))
	{
		return E_FAIL;
	}

	// 協調モードを設定
	//if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_NONEXCLUSIVE | DISCL_FOREGROUND))))
	{
		return E_FAIL;
	}

	// マウスプロパティの設定
	DIPROPDWORD dipdw;
	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = DIPROPAXISMODE_REL; // 相対座標モード
	//dipdw.dwData = DIPROPAXISMODE_ABS; // 絶対座標モード
	if (FAILED(m_pDevice->SetProperty(DIPROP_AXISMODE, &dipdw.diph)))
	{
		return E_FAIL;
	}

	// 接続
	m_pDevice->Acquire();

	return S_OK;
}

/// <summary>
/// 解放
/// </summary>
void CInputMouse::Uninit()
{
	CInput::Uninit();
}

/// <summary>
/// 更新
/// </summary>
void CInputMouse::Update()
{
	// ウィンドウがアクティブかどうか
	HWND hWnd = GetActiveWindow();
	bool isWindowActive = false;
	//if (m_hWnd != hWnd) return;		// アクティブでないならスキップ

	//DIMOUSESTATE dims;
	HRESULT hr = m_pDevice->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&m_dims);
	if(SUCCEEDED(hr))
	{
		// マウスドラッグ処理
		for (int i = 0; i < (int)MouseButtonType::Max; i++)
		{
			// クリック検出
			if ((m_dims.rgbButtons[i] & 128) && m_IsDragArray[i] == false)
			{
				m_IsDragArray[i] = true;
			}
			else if (!(m_dims.rgbButtons[i] & 128))
			{
				// リセット
				m_IsDragArray[i] = false;
			}
		}
		// マウス移動距離保持
		m_CurrentDistance.x = (float)m_dims.lX;		// X軸
		m_CurrentDistance.y = (float)m_dims.lY;		// Y軸
		m_CurrentDistance.z = (float)m_dims.lZ;		// ホイール
	}
	else
	{
		m_pDevice->Unacquire();

		hr = m_pDevice->Acquire();
	}

#if 0

	//// マウス処理
	//for (int i = 0; i < (int)MouseButtonType::Max; i++)
	//{
	//	// クリック検出
	//	MouseInfo* info = &m_MouseInfo[i];
	//	if (GetAsyncKeyState((int)MouseButtonType::L_Button + i) & 0x8000 && info->m_IsDrag == false)
	//	{
	//		info->m_IsDrag = true;
	//		GetCursorPos(&info->m_MousePosStart);
	//	}
	//	else if (!(GetAsyncKeyState((int)MouseButtonType::L_Button + i) & 0x8000))
	//	{
	//		// リセット
	//		info->m_IsDrag = false;
	//		info->m_CurrentDistance = D3DXVECTOR3(0, 0, 0);
	//	}

	//	// ドラッグ処理
	//	if (info->m_IsDrag)
	//	{
	//		// ドラッグ後の現在の座標
	//		GetCursorPos(&info->m_MousePosCurrent);


	//		// 差分を求める
	//		info->m_CurrentDistance.x = (float)(info->m_MousePosCurrent.x - info->m_MousePosStart.x);
	//		info->m_CurrentDistance.y = (float)(info->m_MousePosCurrent.y - info->m_MousePosStart.y);

	//		// 計算後新しい座標を始点とする
	//		GetCursorPos(&info->m_MousePosStart);
	//	}
	//}

#endif
}

/// <summary>
/// ドラッグしているか
/// </summary>
/// <param name="type"></param>
/// <returns></returns>
bool CInputMouse::IsMouseButtonDrag(MouseButtonType type)
{
	return m_IsDragArray[(int)type];
}

/// <summary>
/// マウス情報取得
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
	// ゼロクリア
	memset(&m_joyKeyState, 0, sizeof(XINPUT_STATE));
	memset(&m_joyKeyTrigger, 0, sizeof(XINPUT_STATE));
	memset(&m_joyKeyRelease, 0, sizeof(XINPUT_STATE));
	memset(&m_vibration, 0, sizeof(XINPUT_VIBRATION));
}

CInputPad::~CInputPad()
{

}

/// <summary>
/// 初期設定
/// </summary>
/// <returns></returns>
HRESULT CInputPad::Init()
{
	// 最初のひとつだけで有効
	if(m_padNumAll == 0)
		XInputEnable(true);

	m_padID = m_padNumAll++;

	return S_OK;
}

/// <summary>
/// 解放（XInpu無効化）
/// </summary>
void CInputPad::Uninit()
{
	m_padNumAll--;

	// 最後のひとつで無効
	if(m_padNumAll == 0)
		XInputEnable(false);
}

/// <summary>
/// パッドのPress状態更新
/// </summary>
void CInputPad::Update()
{
	XINPUT_STATE pressState;

	// XInputの入力状態を取得
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
/// 押している
/// </summary>
/// <param name="nKey"></param>
/// <returns></returns>
bool CInputPad::GetPress(InputButton btn)
{
	int nKey = (int)btn;
	return (m_joyKeyState.Gamepad.wButtons & (0x01 << nKey)) ? true : false;
}

/// <summary>
/// 押した瞬間
/// </summary>
/// <param name="btn"></param>
/// <returns></returns>
bool CInputPad::GetTrigger(InputButton btn)
{
	int nKey = (int)btn;
	return (m_joyKeyTrigger.Gamepad.wButtons & (0x01 << nKey)) ? true : false;
}

/// <summary>
/// 離した瞬間
/// </summary>
/// <param name="btn"></param>
/// <returns></returns>
bool CInputPad::GetRelease(InputButton btn)
{
	int nKey = (int)btn;
	return (m_joyKeyRelease.Gamepad.wButtons & (0x01 << nKey)) ? true : false;
}

/// <summary>
/// リピート処理（未実装）
/// </summary>
/// <param name="btn"></param>
/// <returns></returns>
bool CInputPad::GetRepeat(InputButton btn)
{
	return false;
}

/// <summary>
/// 左スティックの傾き
/// </summary>
/// <param name="pOutDir"></param>
/// <returns></returns>
bool CInputPad::GetLeftStickDir(D3DXVECTOR2* pOutDir)
{
	SHORT lx = m_joyKeyState.Gamepad.sThumbLX;
	SHORT ly = m_joyKeyState.Gamepad.sThumbLY;

	// 傾きの値を取得
	if (pOutDir)
	{
		pOutDir->x = GetNormalizedThumb(lx);
		pOutDir->y = GetNormalizedThumb(ly);
	}

	// 傾きの遊び
	if (lx > 80 || lx < -80
		|| ly > 80 || ly < -80)
	{
		return true;
	}

	return false;
}

/// <summary>
/// 右スティックの傾き
/// </summary>
/// <param name="pOutDir"></param>
/// <returns></returns>
bool CInputPad::GetRightStickDir(D3DXVECTOR2* pOutDir)
{
	SHORT rx = m_joyKeyState.Gamepad.sThumbRX;
	SHORT ry = m_joyKeyState.Gamepad.sThumbRY;

	// 傾きの値を取得
	if (pOutDir)
	{
		pOutDir->x = GetNormalizedThumb(rx);
		pOutDir->y = GetNormalizedThumb(ry);
	}

	// 傾きの遊び
	if (rx > 80 || rx < -80
		|| ry > 80 || ry < -80)
	{
		return true;
	}

	return false;
}

/// <summary>
/// スティックの傾き値（-32768～32767）を正規化
/// </summary>
/// <param name="sThumb"></param>
/// <returns></returns>
float CInputPad::GetNormalizedThumb(SHORT sThumb)
{
	return (sThumb >= 0) ? sThumb / 32767.f : sThumb / 32768.f;
}

/// <summary>
/// バイブレーション設定
/// </summary>
void CInputPad::SetVibrationEnable(bool enable)
{
	int value = (enable == true) ? 65535 : 0;

	m_vibration.wLeftMotorSpeed = value;
	m_vibration.wRightMotorSpeed = value;

	// コントローラーの状態を設定する
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
/// 初期設定
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
/// 解放
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
/// 更新処理
/// </summary>
void CInputManager::Update()
{
	if (m_pKeyboard != nullptr)
		m_pKeyboard->Update();

	if (m_pPad != nullptr)
		m_pPad->Update();
}

/// <summary>
/// 押している
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
/// 押した瞬間
/// </summary>
/// <param name="type"></param>
/// <returns></returns>
bool CInputManager::GetTrigger(InputType type)
{
	return m_pKeyboard->GetTrigger(ConvertToKeyboard(type)) || 
		m_pPad->GetTrigger(ConvertToPad(type));
}

/// <summary>
/// 離した瞬間
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
/// キーボード入力へ変換
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
/// パッド入力へ変換
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
//*********************************************
//
// ���͏���(input.h)
// Author : Junichi Uchiyama
//
//*********************************************

#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

#include <functional>

/// <summary>
/// ���͊Ǘ�
/// </summary>
class CInput
{
public:
	//---------------------
	// public Method
	CInput();													// �R���X�g���N�^
	virtual ~CInput();											// �f�X�g���N�^

	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);		// ������
	virtual void Uninit();										// ���
	virtual void Update() = 0;									// �X�V

protected:
	//---------------------
	// public Member
	LPDIRECTINPUTDEVICE8 m_pDevice;		// �f�o�C�X
	static LPDIRECTINPUT8 m_pInput;		// ���͊Ǘ�
};

/// <summary>
/// �L�[�{�[�h����
/// </summary>
class CInputKeyboard : public CInput
{
public:
	//---------------------
	// public Method
	CInputKeyboard();											// �R���X�g���N�^
	~CInputKeyboard() override;									// �f�X�g���N�^

	HRESULT Init(HINSTANCE hInstance, HWND hWnd) override;		// ������
	void Uninit() override;										// ���
	void Update() override;										// �X�V

	//---------------------
	// Getter
	bool GetPress(int nKey);				// �����Ă���
	bool GetTrigger(int nKey);				// ��������
	bool GetRelease(int nKey);				// ������
	bool GetRepeat(int nKey);				// �J��Ԃ�����

private:
	static const int MAX_KEY = 256;			// �L�[�ő吔
	BYTE m_aKeyState[MAX_KEY];				// �v���X���
	BYTE m_aKeyStateTrigger[MAX_KEY];		// �g���K�[���
	BYTE m_aKeyStateRelease[MAX_KEY];		// �����[�X���
};

/// <summary>
/// �}�E�X����
/// </summary>
class CInputMouse : public CInput
{
public:
	//---------------------
	// enum
	enum class MouseButtonType
	{
		Left = 0,
		Right,
		Center,

		Max
	};

	//---------------------
	// public Method
	CInputMouse();									// �R���X�g���N�^
	~CInputMouse();									// �f�X�g���N�^

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// ������
	void Uninit();									// ���
	void Update();									// �X�V

	bool IsMouseButtonDrag(MouseButtonType type);	// �}�E�X���h���b�O���Ă��邩
	D3DXVECTOR3& GetMouseMoveDist();

	void DebugDraw();								// �f�o�b�O�`��

private:
	//---------------------
	// public Member
	HWND m_hWnd;									// �ێ�
	DIMOUSESTATE m_dims;							// �ێ�
	bool m_IsDragArray[(int)MouseButtonType::Max];	// �}�E�X�h���b�O���
	D3DXVECTOR3 m_CurrentDistance;					// �}�E�X�ړ������ێ��iZ�̓z�C�[���j
};

/// <summary>
/// �p�b�h����
/// </summary>
class CInputPad : public CInput
{
public:
	//---------------------
	// enum
	enum class InputButton
	{
		Button_Up = 0,		// �\���L�[:��
		Button_Down,		// �\���L�[:��
		Button_Left,		// �\���L�[:��
		Button_Right,		// �\���L�[:�E
		Button_Start,		// Start�{�^��
		Button_Back,		// Back�{�^��
		Button_Stick_L3,	// ���X�e�B�b�N��������
		Button_Stick_R3,	// �E�X�e�B�b�N��������
		Button_Stick_L1,	// LB�{�^��
		Button_Stick_R1,	// RB�{�^��
		Button_Dummy1,		// �_�~�[
		Button_Dummy2,		// �_�~�[
		Button_A,			// �`�{�^��
		Button_B,			// �a�{�^��
		Button_X,			// �w�{�^��
		Button_Y,			// �x�{�^��
		Max,
		Invalid,			// ����
	};

	//---------------------
	// public Method
	CInputPad();
	~CInputPad();

	HRESULT Init();									// �����ݒ�
	void Uninit();									// ���
	void Update();									// �X�V

	void SetVibrationEnable(bool enable);						// �o�C�u���[�V�����L��

	//---------------------
	// Getter
	bool GetPress(InputButton btn);				// �����Ă���
	bool GetTrigger(InputButton btn);			// ��������
	bool GetRelease(InputButton btn);			// ������
	bool GetRepeat(InputButton btn);			// �J��Ԃ�����
	bool GetLeftStickDir(D3DXVECTOR2* pOutDir);		// �X�e�B�b�N���
	bool GetRightStickDir(D3DXVECTOR2* pOutDir);		// �X�e�B�b�N���

private:
	//---------------------
	// private Member
	XINPUT_STATE m_joyKeyState;						// �p�b�h���
	XINPUT_STATE m_joyKeyTrigger;					// �g���K�[���
	XINPUT_STATE m_joyKeyRelease;					// �����[�X���
	XINPUT_VIBRATION m_vibration;					// �o�C�u���[�V����

	int m_padID;									// �p�b�h�̔ԍ�
	static int m_padNumAll;							// �p�b�h�̑���

	float GetNormalizedThumb(SHORT sThumb);			// �X�e�B�b�N�̌X���l�𐳋K��
};

/// <summary>
/// �L�[�{�[�h�ƃp�b�h���ꊇ�Ŕ���
/// </summary>
class CInputManager
{
public:
	//---------------------
	// enum
	enum class InputType
	{
		Decide_A,			// A�{�^��*ENTER
		Cancel_B,			// B�{�^��*BackSpace
		Action_X,			// X�{�^��*E�L�[
		Action_Y,			// Y�{�^��*R�L�[
		Move_Up,			// �\����*W�L�[*���X�e�B�b�N�ړ�
		Move_Down,			// �\����*S�L�[*���X�e�B�b�N�ړ�
		Move_Left,			// �\����*A�L�[*���X�e�B�b�N�ړ�
		Move_Right,			// �\���E*D�L�[*���X�e�B�b�N�ړ�
		StartPause,			// �X�^�[�g�{�^��*P�L�[
		Max,
	};

	//---------------------
	// public Method
	CInputManager();
	~CInputManager();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit();
	void Update();

	//---------------------
	// Getter
	bool GetPress(InputType type);			// �����Ă���
	bool GetTrigger(InputType type);		// ��������
	bool GetRelease(InputType type);		// ������
	// ��{���̃N���X��Getter���g������p�ŗ~�����ꍇ�͎擾
	CInputKeyboard* GetKeyboard() { return m_pKeyboard; }
	CInputPad* GetPad() { return m_pPad; }
private:
	//---------------------
	// private Member
	CInputKeyboard* m_pKeyboard;
	CInputPad* m_pPad;

	//---------------------
	// private Method
	int ConvertToKeyboard(InputType type);					// �L�[�{�[�h�p�ɕϊ�
	CInputPad::InputButton ConvertToPad(InputType type);	// �p�b�h�p�ɕϊ�
	bool GetPressMove(InputType type);		// +���œ��͂ɍ��킹�����L�[
};

#endif
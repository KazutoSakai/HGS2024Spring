//*********************************************
//
// 入力処理(input.h)
// Author : Junichi Uchiyama
//
//*********************************************

#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

#include <functional>

/// <summary>
/// 入力管理
/// </summary>
class CInput
{
public:
	//---------------------
	// public Method
	CInput();													// コンストラクタ
	virtual ~CInput();											// デストラクタ

	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);		// 初期化
	virtual void Uninit();										// 解放
	virtual void Update() = 0;									// 更新

protected:
	//---------------------
	// public Member
	LPDIRECTINPUTDEVICE8 m_pDevice;		// デバイス
	static LPDIRECTINPUT8 m_pInput;		// 入力管理
};

/// <summary>
/// キーボード入力
/// </summary>
class CInputKeyboard : public CInput
{
public:
	//---------------------
	// public Method
	CInputKeyboard();											// コンストラクタ
	~CInputKeyboard() override;									// デストラクタ

	HRESULT Init(HINSTANCE hInstance, HWND hWnd) override;		// 初期化
	void Uninit() override;										// 解放
	void Update() override;										// 更新

	//---------------------
	// Getter
	bool GetPress(int nKey);				// 押している
	bool GetTrigger(int nKey);				// 押した時
	bool GetRelease(int nKey);				// 離した
	bool GetRepeat(int nKey);				// 繰り返し処理

private:
	static const int MAX_KEY = 256;			// キー最大数
	BYTE m_aKeyState[MAX_KEY];				// プレス情報
	BYTE m_aKeyStateTrigger[MAX_KEY];		// トリガー情報
	BYTE m_aKeyStateRelease[MAX_KEY];		// リリース情報
};

/// <summary>
/// マウス入力
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
	CInputMouse();									// コンストラクタ
	~CInputMouse();									// デストラクタ

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// 初期化
	void Uninit();									// 解放
	void Update();									// 更新

	bool IsMouseButtonDrag(MouseButtonType type);	// マウスをドラッグしているか
	D3DXVECTOR3& GetMouseMoveDist();

	void DebugDraw();								// デバッグ描画

private:
	//---------------------
	// public Member
	HWND m_hWnd;									// 保持
	DIMOUSESTATE m_dims;							// 保持
	bool m_IsDragArray[(int)MouseButtonType::Max];	// マウスドラッグ状態
	D3DXVECTOR3 m_CurrentDistance;					// マウス移動距離保持（Zはホイール）
};

/// <summary>
/// パッド入力
/// </summary>
class CInputPad : public CInput
{
public:
	//---------------------
	// enum
	enum class InputButton
	{
		Button_Up = 0,		// 十字キー:上
		Button_Down,		// 十字キー:下
		Button_Left,		// 十字キー:左
		Button_Right,		// 十字キー:右
		Button_Start,		// Startボタン
		Button_Back,		// Backボタン
		Button_Stick_L3,	// 左スティック押し込み
		Button_Stick_R3,	// 右スティック押し込み
		Button_Stick_L1,	// LBボタン
		Button_Stick_R1,	// RBボタン
		Button_Dummy1,		// ダミー
		Button_Dummy2,		// ダミー
		Button_A,			// Ａボタン
		Button_B,			// Ｂボタン
		Button_X,			// Ｘボタン
		Button_Y,			// Ｙボタン
		Max,
		Invalid,			// 無効
	};

	//---------------------
	// public Method
	CInputPad();
	~CInputPad();

	HRESULT Init();									// 初期設定
	void Uninit();									// 解放
	void Update();									// 更新

	void SetVibrationEnable(bool enable);						// バイブレーション有効

	//---------------------
	// Getter
	bool GetPress(InputButton btn);				// 押している
	bool GetTrigger(InputButton btn);			// 押した時
	bool GetRelease(InputButton btn);			// 離した
	bool GetRepeat(InputButton btn);			// 繰り返し処理
	bool GetLeftStickDir(D3DXVECTOR2* pOutDir);		// スティック状態
	bool GetRightStickDir(D3DXVECTOR2* pOutDir);		// スティック状態

private:
	//---------------------
	// private Member
	XINPUT_STATE m_joyKeyState;						// パッド情報
	XINPUT_STATE m_joyKeyTrigger;					// トリガー情報
	XINPUT_STATE m_joyKeyRelease;					// リリース情報
	XINPUT_VIBRATION m_vibration;					// バイブレーション

	int m_padID;									// パッドの番号
	static int m_padNumAll;							// パッドの総数

	float GetNormalizedThumb(SHORT sThumb);			// スティックの傾き値を正規化
};

/// <summary>
/// キーボードとパッドを一括で判定
/// </summary>
class CInputManager
{
public:
	//---------------------
	// enum
	enum class InputType
	{
		Decide_A,			// Aボタン*ENTER
		Cancel_B,			// Bボタン*BackSpace
		Action_X,			// Xボタン*Eキー
		Action_Y,			// Yボタン*Rキー
		Move_Up,			// 十字上*Wキー*左スティック移動
		Move_Down,			// 十字下*Sキー*左スティック移動
		Move_Left,			// 十字左*Aキー*左スティック移動
		Move_Right,			// 十字右*Dキー*左スティック移動
		StartPause,			// スタートボタン*Pキー
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
	bool GetPress(InputType type);			// 押している
	bool GetTrigger(InputType type);		// 押した時
	bool GetRelease(InputType type);		// 離した
	// 基本このクラスのGetterを使うが専用で欲しい場合は取得
	CInputKeyboard* GetKeyboard() { return m_pKeyboard; }
	CInputPad* GetPad() { return m_pPad; }
private:
	//---------------------
	// private Member
	CInputKeyboard* m_pKeyboard;
	CInputPad* m_pPad;

	//---------------------
	// private Method
	int ConvertToKeyboard(InputType type);					// キーボード用に変換
	CInputPad::InputButton ConvertToPad(InputType type);	// パッド用に変換
	bool GetPressMove(InputType type);		// +αで入力に合わせたいキー
};

#endif
//*********************************************
//
// アプリケーション(application.h)
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
/// アプリケーション動作に必要な要素を管理
/// </summary>
class CApplication
{
public:

	//---------------------
	// 定数
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
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);		// 初期化
	void Uninit();						// 解放
	void Update();						// 更新
	void Draw();						// 描画

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
	CApplication();						// コンストラクタ
	~CApplication();					// デストラクタ

	//---------------------
	// Member
	bool m_bPause;						// ポーズ中かどうか

	//---------------------
	// library
	CRenderer* m_pRenderer;				// オブジェクト描画
	CInputManager* m_pInputManager;	// キーボード入力
	CInputMouse* m_pInputMouse;			// マウス入力
	CSound* m_pSound;					// サウンド
	CView* m_pView;						// ビュー(カメラ)
	CTexture* m_pTexture;				// テクスチャ管理
	CLight* m_pLight;					// ライト管理

	//---------------------
	// Application
	CSceneManager* m_pSceneManager;		// シーン遷移管理

#ifdef _DEBUG
	bool m_IsDebugCamera;				// カメラのデバッグ切り替え
#endif
};

#endif
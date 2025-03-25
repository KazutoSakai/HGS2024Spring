//*********************************************
//
// アプリケーション(application.cpp)
// Author : Junichi Uchiyama
//
//*********************************************

#include "application.h"

#include "light.h"

/// <summary>
/// コンストラクタ
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
/// デストラクタ
/// </summary>
CApplication::~CApplication()
{

}

/// <summary>
/// 初期化
/// </summary>
/// <param name="hWnd"></param>
/// <param name="bWindow"></param>
/// <returns></returns>
HRESULT CApplication::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// レンダラー
	m_pRenderer = DBG_NEW CRenderer();
	m_pRenderer->Init(hWnd, bWindow);

	// キーボード
	m_pInputManager = DBG_NEW CInputManager();
	m_pInputManager->Init(hInstance, hWnd);

	// マウス
	m_pInputMouse = DBG_NEW CInputMouse();
	m_pInputMouse->Init(hInstance, hWnd);

	// サウンド
	m_pSound = DBG_NEW CSound();
	m_pSound->Init(hWnd);

	// ビュー
	m_pView = CView::Create();
	m_pView->SetFlgManualDelete(true);

	// テクスチャ
	m_pTexture = DBG_NEW CTexture();

	// ライト初期化
	m_pLight = DBG_NEW CLight();
	m_pLight->Init();

	// シーン読込
	m_pSceneManager = DBG_NEW CSceneManager();
	m_pSceneManager->Init();

	return S_OK;
}

/// <summary>
/// 解放
/// </summary>
void CApplication::Uninit()
{
	// 全解放
	CObject::ReleaseAll();

	// 手動解放
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
/// 更新
/// </summary>
void CApplication::Update()
{
	// キーボード入力更新
	if (m_pInputManager != nullptr)
	{
		m_pInputManager->Update();

#ifdef _DEBUG
		// カメラデバッグ操作が可能
		DebugUpdateCamera();
#endif

	}

	// マウス入力更新
	if (m_pInputMouse != nullptr)
		m_pInputMouse->Update();

	// ポーズ中は以下の処理を実行しない
	if (m_bPause)
		return;

	// 各シーンごとの更新処理
	if (m_pSceneManager != nullptr)
		m_pSceneManager->Update();

	// オブジェクトの更新
	if (m_pRenderer != nullptr)
		m_pRenderer->Update();
}

/// <summary>
/// 描画
/// </summary>
void CApplication::Draw()
{
	// 各シーンごとの描画
	if(m_pSceneManager != nullptr)
		m_pSceneManager->Draw();

	// オブジェクトの描画
	if (m_pRenderer != nullptr)
		m_pRenderer->Draw();
}

#ifdef _DEBUG

void CApplication::DebugUpdateCamera()
{

	// デバッグ
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
	sprintf(&text[0], "カメラデバッグ切替：F2");
	m_pRenderer->DebugDrawText(text);
#endif
}

#endif
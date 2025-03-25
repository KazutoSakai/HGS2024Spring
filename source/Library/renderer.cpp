//*********************************************
//
// 描画クラス(renderer.cpp)
// Author : Junichi Uchiyama
//
//*********************************************

#include "renderer.h"
#include "object.h"
#include "application.h"

int CRenderer::m_debugTextPos = 0;
LPD3DXFONT CRenderer::m_pFont = nullptr;

/// <summary>
/// コンストラクタ
/// </summary>
CRenderer::CRenderer()
{
	m_pD3D = nullptr;
	m_pD3DDevice = nullptr;
	m_pFont = nullptr;
}

/// <summary>
/// デストラクタ
/// </summary>
CRenderer::~CRenderer()
{

}

/// <summary>
/// レンダラー初期化
/// </summary>
/// <param name="hWnd"></param>
/// <param name="bWindow"></param>
/// <returns></returns>
HRESULT CRenderer::Init(HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;			// ディスプレイモード
	D3DPRESENT_PARAMETERS d3dpp;	// プレゼンテーションパラメータ

	// Direct3Dオブジェクトの生成
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}

	// 現在のディスプレイモードを取得
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータ
	ZeroMemory(&d3dpp, sizeof(d3dpp));					// パラメータのクリア

	d3dpp.BackBufferWidth = SCREEN_WIDTH;						// ゲーム画面サイズ（幅）
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;						// ゲーム画面サイズ（高さ）
	d3dpp.BackBufferFormat = d3ddm.Format;						// バックバッファの形式
	d3dpp.BackBufferCount = 1;									// バックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;					// ダブルバッファの切り替え（映像信号に同期）
	d3dpp.EnableAutoDepthStencil = TRUE;						// デプスバッファとステンシルバッファを作成
	//d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					// デプスバッファとして16bit使う
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;				// ステンシルバッファ用
	d3dpp.Windowed = bWindow;									// ウィンドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	// リフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// インターバル

	// Direct3Dデバイスの生成（描画処理と頂点処理をハードウェアで行う
	if (FAILED(m_pD3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&m_pD3DDevice)))
	{
		// Direct3Dデバイスの生成（描画処理はハードウェア、頂点処理はCPUで行う
		if (FAILED(m_pD3D->CreateDevice(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&m_pD3DDevice)))
		{
			// Direct3Dデバイスの生成（描画処理と頂点処理をCPUで行う
			if (FAILED(m_pD3D->CreateDevice(
				D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&m_pD3DDevice)))
			{
			return E_FAIL;
			}
		}
	}

	// レンダーステートの設定
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// サンプラーステート
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	// テクスチャステージステート
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	// デバッグ表示用のフォントを生成
	D3DXCreateFont(
		m_pD3DDevice, 18, 0, 0, 0,
		FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"Terminal", &m_pFont);

	return S_OK;
}

/// <summary>
/// 終了処理
/// </summary>
void CRenderer::Uninit()
{
	// デバッグ表示用フォントの破棄
	if (m_pFont != NULL)
	{
		m_pFont->Release();
		m_pFont = NULL;
	}

	// Direct3Dデバイスの破棄
	if (m_pD3DDevice != NULL)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = NULL;
	}

	// Direct3Dオブジェクトの破棄
	if (m_pD3D != NULL)
	{
		m_pD3D->Release();
		m_pD3D = NULL;
	}
}

/// <summary>
/// 更新処理
/// </summary>
void CRenderer::Update()
{
	CObject::UpdateAll();
}

/// <summary>
/// 描画処理
/// </summary>
void CRenderer::Draw()
{
	//// 画面クリア（バックバッファ＆Zバッファのクリア）
	//m_pD3DDevice->Clear(0, NULL,
	//	(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
	//	D3DCOLOR_RGBA(0, 125, 255, 255), 1.0f, 0);

	// 画面クリア（ステンシルバッファ＆バックバッファ＆Zバッファのクリア）
	m_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_STENCIL | D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DXCOLOR(RENDER_COL), 1.0f, 0);

	// 描画開始
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{// 描画開始が成功した場合

		CObject::DrawAll();

#ifdef _DEBUG

		// FPSの表示
		m_debugTextPos = 0;
		DrawFPS();

		CObject::DrawDebugAll();

		CApplication::GetInstance()->DebugDraw();

#endif

	}

	// 描画終了
	m_pD3DDevice->EndScene();

	// バックバッファとフロントバッファの入れ替え
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

/// <summary>
/// デバイス取得
/// </summary>
/// <returns></returns>
LPDIRECT3DDEVICE9 CRenderer::GetDevice()
{
	return m_pD3DDevice;
}

/// <summary>
/// 描画設定
/// </summary>
void CRenderer::SetRenderState(RENDER_STATE state)
{
	switch (state)
	{
	case CRenderer::DEFAULT:
		m_pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		break;
	case CRenderer::ADD:
		m_pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		break;
	default:
		break;
	}
}

/// <summary>
/// FPS描画
/// </summary>
void CRenderer::DrawFPS()
{
	int nCountFPS = GetFPS();

	// FPS表示
	RECT rect = { 0, (int)m_debugTextPos, SCREEN_WIDTH, SCREEN_HEIGHT };
	char aStr[256];

	// 文字列に代入
	sprintf(&aStr[0], "FPS.%d\n", nCountFPS);

	// テキストの描画
	m_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));

	m_debugTextPos += 18;
}

void CRenderer::DebugDrawText(char* text)
{
	RECT rect = { 0, (int)m_debugTextPos, SCREEN_WIDTH, SCREEN_HEIGHT };

	// テキストの描画
	m_pFont->DrawText(NULL, text, -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));

	m_debugTextPos += 18;
}
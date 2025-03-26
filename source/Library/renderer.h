//*********************************************
//
// 描画クラス(renderer.h)
// Author : Junichi Uchiyama
//
//*********************************************

#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "main.h"

/// <summary>
/// レンダラークラス
/// </summary>
class CRenderer
{
public:
	//---------------------
	// enum

	// 描画設定
	enum RENDER_STATE
	{
		DEFAULT,		// 通常
		ADD,			// 加算合成

		MAX,
	};

	//---------------------
	// public Method
	CRenderer();		// コンストラクタ
	~CRenderer();		// デストラクタ

	HRESULT Init(HWND hWnd, BOOL bWindow);		// 初期化
	void Uninit();		// 破棄
	void Update();		// 更新
	void Draw();		// 描画

	LPDIRECT3DDEVICE9 GetDevice();				// デバイスの取得
	void SetRenderState(RENDER_STATE state);	// 描画設定

	static void DebugDrawText(char* text);

private:
	//---------------------
	// private Method
	void DrawFPS();		// FPS描画

	//---------------------
	// private Member
	LPDIRECT3D9 m_pD3D;					// Direct3Dオブジェクトへのポインタ
	LPDIRECT3DDEVICE9 m_pD3DDevice;		// Direct3Dデバイスへのポインタ

	//---------------------
	// static Member
	static const DWORD RENDER_COL = 0xff000000;
	static LPD3DXFONT m_pFont;			// フォントへのポインタ
	static int m_debugTextPos;
};

#endif
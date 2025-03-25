//*********************************************
//
// メインヘッダー(main.h)
// Author : Junichi Uchiyama
//
//*********************************************

#ifndef _MAIN_H_
#define _MAIN_H_

#include <Windows.h>
#include "d3dx9.h"						// 描画処理に必要
#define DIRECTINPUT_VERSION (0x800)		// ビルド時の警告対処用マクロ
#include "dinput.h"						// 入力処理に必要
#include "xaudio2.h"					// サウンド処理に必要
#include "Xinput.h"						// パッド処理に必要
#include <assert.h>						// デバッグ用

#pragma comment (lib, "d3d9.lib")		// 描画処理に必要
#pragma comment (lib, "d3dx9.lib")		// [d3d9.lib]の拡張ライブラリ
#pragma comment (lib, "dxguid.lib")		// DirectXコンポーネント（部品）使用に必要
#pragma comment (lib, "winmm.lib")		// ｼｽﾃﾑ時刻取得に必要
#pragma comment (lib, "dinput8.lib")	// 入力処理に必要
#pragma comment (lib, "xinput.lib")		// パッド処理に必要

// マクロ定義
#define SCREEN_WIDTH	(1280)						// ウィンドウの幅
#define SCREEN_HEIGHT	(720)						// ウィンドウの高さ
#define CLASS_NAME			"WindowClass"			// ウィンドウクラスの名前
#define WINDOW_NAME			"C++ゲーム制作"			// ウィンドウの名前

// デバッグnew
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdio.h>
#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

// プロトタイプ宣言
int GetFPS(void);						// FPSカウンター取得
float GetWorldDeltaSeconds(void);		// フレーム間の秒数

#endif
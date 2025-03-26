//*********************************************
//
// C++ゲーム制作(main.cpp)
// Author : Junichi Uchiyama
//
//*********************************************

// ファイル読み込み
#include "main.h"
#include "application.h"

// プロトタイプ宣言
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
bool OutputFinishedMessageBox(HWND hWnd);

// グローバル変数
int g_nCountFPS = 0;			// FPSカウンター
float g_fDeltaSecond = 0.0f;	// Deltaタイム

/// <summary>
/// メイン関数
/// </summary>
/// <param name="hInstance">このアプリケーションのインスタンスハンドル（識別子）</param>
/// <param name="hInstancePrev">常にNULL</param>
/// <param name="lpCmdLine">コマンドラインで受け取った引数へのポインタ</param>
/// <param name="nCmdShow">初期ウィンドウの表示方法</param>
/// <returns></returns>
int WINAPI WinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hInstancePrev,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow)
{
	//_CrtSetBreakAlloc(1061);

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),					// WNDCLASSEXのメモリサイズ
		CS_CLASSDC,							// ウィンドウのスタイル
		WindowProc,							// ウィンドウプロシージャ
		0,									// ０にする（通常はしない）
		0,									// ０にする（通常はしない）
		hInstance,							// インスタンスハンドル
		LoadIcon(NULL, IDI_APPLICATION),	// タスクバーのアイコン
		LoadCursor(NULL, IDC_ARROW),		// マウスカーソル
		(HBRUSH)(COLOR_WINDOW + 1),			// クライアント領域の背景色
		NULL,								// メニューバー
		CLASS_NAME,							// ウィンドウクラスの名前
		LoadIcon(NULL, IDI_APPLICATION)		// ファイルのアイコン
	};

	HWND hWnd;					// ウィンドウハンドル（識別子）
	MSG msg;					// メッセージを格納する変数
	RECT rect = { 0,0,SCREEN_WIDTH, SCREEN_HEIGHT };	// 画面サイズの構造体
	DWORD dwCurrentTime;		// 現在時刻
	DWORD dwExecLastTime;		// 最後に処理した時刻
	DWORD dwFrameCount;			// フレームカウント
	DWORD dwFPSLastTime;		// 最後にFPSを計測した時刻

	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	// クライアント老域を指定のサイズに調整
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	// ウィンドウを生成
	hWnd = CreateWindowEx(0,		// 拡張ウィンドウスタイル
		CLASS_NAME,					// ウィンドウクラスの名前
		WINDOW_NAME,				// ウィンドウの名前
		WS_OVERLAPPEDWINDOW,		// ウィンドウスタイル
		CW_USEDEFAULT,				// ウィンドウの左上ｘ座標
		CW_USEDEFAULT,				// ウィンドウの左上ｙ座標
		(rect.right - rect.left),	// ウィンドウの幅
		(rect.bottom - rect.top),	// ウィンドウの高さ
		NULL,						// 親ウィンドウのハンドル
		NULL,						// メニューハンドルまたは子ウィンドウID
		hInstance,					// ウィンドウ作成データ
		NULL);

	// 初期化処理
	CApplication* pApp = CApplication::GetInstance();
	pApp->Init(hInstance, hWnd, TRUE);

	// 分解能を設定
	timeBeginPeriod(1);
	dwCurrentTime = 0;					// 初期化する
	dwExecLastTime = timeGetTime();		// 現在時刻を取得（保存）
	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();

	// ウィンドウの表示
	ShowWindow(hWnd, nCmdShow);			// ウィンドウの表示状態を設定
	UpdateWindow(hWnd);					// クライアント領域を更新

	// メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{// Windowsの処理
			if (msg.message == WM_QUIT)
			{// WM_QUITメッセージを受け取ったらメッセージループを抜ける
				break;
			}
			else
			{
				// メッセージの設定
				TranslateMessage(&msg);			// 仮想キーメッセージを文字メッセージへ変換
				DispatchMessage(&msg);			// ウィンドウプロシージャへメッセージを送出
			}
		}
		else
		{// DirectXの処理
			dwCurrentTime = timeGetTime();		// 現在時刻を取得
			
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{// 0.5秒経過
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;		// FPSを測定した時刻を保存
				dwFrameCount = 0;					// フレームカウントをクリア
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{// 60分の1秒経過

				g_fDeltaSecond = (float)(dwCurrentTime - dwExecLastTime);

				dwExecLastTime = dwCurrentTime;		// 処理開始の時刻（現在時刻）を保存

				// 更新
				pApp->Update();

				// 描画
				pApp->Draw();

				// フレームカウントを加算
				dwFrameCount++;
			}
		}
	}

	// 終了処理
	if (pApp != nullptr)
	{
		pApp->Uninit();
	}

	// 分解能を戻す
	timeEndPeriod(1);

	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// メモリリーク検出
	_CrtDumpMemoryLeaks();

	return (int)msg.wParam;
}

/// <summary>
/// ウィンドウプロシージャ
/// </summary>
/// <param name="hWnd">ウィンドウハンドル（識別子）</param>
/// <param name="uMsg">メッセージ</param>
/// <param name="wParam">パラメータその１</param>
/// <param name="lParam">パラメータその２</param>
/// <returns></returns>
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	bool result = false;

	switch (uMsg)
	{
	case WM_DESTROY:		// ウィンドウ破棄メッセージ
		// WM_QUITメッセージを送る
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:		// キー押下のメッセージ
		switch (wParam)
		{
		case VK_ESCAPE:		// ESCキーが押された
			// ウィンドウを破棄する（WM_DESTROYメッセージを送る）
			result = OutputFinishedMessageBox(hWnd);
			if (result == true)
			{
				// ウィンドウを破棄する
				DestroyWindow(hWnd);
			}
			break;
		}
		break;
	case WM_CLOSE:			// 閉じるボタン押下のメッセージ
		result = OutputFinishedMessageBox(hWnd);
		if (result == true)
		{
			// ウィンドウを破棄する
			DestroyWindow(hWnd);
		}
		else
		{
			return 0;		// WM_CLOSEメッセージの返事は0を返さないと終了してしまう
		}
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

/// <summary>
/// 終了メッセージBOX
/// </summary>
/// <param name="hWnd"></param>
/// <returns>true：終了、false：終了しない</returns>
bool OutputFinishedMessageBox(HWND hWnd)
{
	int nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO | MB_ICONQUESTION);

	return (nID == IDYES) ? true : false;
}


/// <summary>
/// FPSカウンター取得
/// </summary>
/// <returns></returns>
int GetFPS()
{
	return g_nCountFPS;
}

/// <summary>
/// フレーム間の秒数
/// </summary>
/// <returns></returns>
float GetWorldDeltaSeconds()
{
	return g_fDeltaSecond * 0.001f;
}
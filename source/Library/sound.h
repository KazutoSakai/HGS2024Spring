//*********************************************
//
// サウンド(sound.h)
// Author : Junichi Uchiyama
//
//*********************************************

#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

/// <summary>
/// サウンドクラス
/// </summary>
class CSound
{
public:

	//---------------------
	// enum

	// サウンドの種類
	enum SOUND_LABEL
	{
		// 仮
		BGM000 = 0,
		BGM001,
		BGM002,

		SE_SHOT,
		SE_HIT,
		SE_EXPLOSION,

		SE_DRUM,	// ドラムロール
		SE_CRAP,
		MAX,
	};

	//---------------------
	// public Method
	CSound();							// コンストラクタ
	~CSound();							// デストラクタ

	HRESULT Init(HWND hWnd);			// 初期化
	void Uninit();						// 解放
	HRESULT Play(SOUND_LABEL label);	// 再生
	void Stop(SOUND_LABEL label);		// 停止（指定）
	void Stop();						// 停止（全）

private:

	//---------------------
	// struct
	struct PARAM
	{
		const char* pFilename;		// ファイル名
		int nCntLoop;				// ループカウント
	};

	//---------------------
	// private Method
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPos);		// チャンクデータ確認
	HRESULT ReadChunk(HANDLE hFile, void* pBuffer, DWORD dwBufferSize, DWORD dwBufferOffset);		// チャンクデータ読込

	//---------------------
	// Audio関連
	IXAudio2 *m_pXAudio2;
	IXAudio2MasteringVoice *m_pMasteringVoice;
	IXAudio2SourceVoice* m_apSourceVoice[SOUND_LABEL::MAX];
	BYTE* m_apDataAudio[SOUND_LABEL::MAX];
	DWORD m_aSizeAudio[SOUND_LABEL::MAX];
	PARAM m_param[SOUND_LABEL::MAX];							// サウンドの情報はここへ格納

};

#endif
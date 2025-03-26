//*********************************************
//
// �T�E���h(sound.h)
// Author : Junichi Uchiyama
//
//*********************************************

#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

/// <summary>
/// �T�E���h�N���X
/// </summary>
class CSound
{
public:

	//---------------------
	// enum

	// �T�E���h�̎��
	enum SOUND_LABEL
	{
		// ��
		BGM000 = 0,
		BGM001,
		BGM002,

		SE_SHOT,
		SE_HIT,
		SE_EXPLOSION,

		SE_DRUM,	// �h�������[��
		SE_CRAP,
		MAX,
	};

	//---------------------
	// public Method
	CSound();							// �R���X�g���N�^
	~CSound();							// �f�X�g���N�^

	HRESULT Init(HWND hWnd);			// ������
	void Uninit();						// ���
	HRESULT Play(SOUND_LABEL label);	// �Đ�
	void Stop(SOUND_LABEL label);		// ��~�i�w��j
	void Stop();						// ��~�i�S�j

private:

	//---------------------
	// struct
	struct PARAM
	{
		const char* pFilename;		// �t�@�C����
		int nCntLoop;				// ���[�v�J�E���g
	};

	//---------------------
	// private Method
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPos);		// �`�����N�f�[�^�m�F
	HRESULT ReadChunk(HANDLE hFile, void* pBuffer, DWORD dwBufferSize, DWORD dwBufferOffset);		// �`�����N�f�[�^�Ǎ�

	//---------------------
	// Audio�֘A
	IXAudio2 *m_pXAudio2;
	IXAudio2MasteringVoice *m_pMasteringVoice;
	IXAudio2SourceVoice* m_apSourceVoice[SOUND_LABEL::MAX];
	BYTE* m_apDataAudio[SOUND_LABEL::MAX];
	DWORD m_aSizeAudio[SOUND_LABEL::MAX];
	PARAM m_param[SOUND_LABEL::MAX];							// �T�E���h�̏��͂����֊i�[

};

#endif
//*********************************************
//
// ���C���w�b�_�[(main.h)
// Author : Junichi Uchiyama
//
//*********************************************

#ifndef _MAIN_H_
#define _MAIN_H_

#include <Windows.h>
#include "d3dx9.h"						// �`�揈���ɕK�v
#define DIRECTINPUT_VERSION (0x800)		// �r���h���̌x���Ώ��p�}�N��
#include "dinput.h"						// ���͏����ɕK�v
#include "xaudio2.h"					// �T�E���h�����ɕK�v
#include "Xinput.h"						// �p�b�h�����ɕK�v
#include <assert.h>						// �f�o�b�O�p

#pragma comment (lib, "d3d9.lib")		// �`�揈���ɕK�v
#pragma comment (lib, "d3dx9.lib")		// [d3d9.lib]�̊g�����C�u����
#pragma comment (lib, "dxguid.lib")		// DirectX�R���|�[�l���g�i���i�j�g�p�ɕK�v
#pragma comment (lib, "winmm.lib")		// ���ю����擾�ɕK�v
#pragma comment (lib, "dinput8.lib")	// ���͏����ɕK�v
#pragma comment (lib, "xinput.lib")		// �p�b�h�����ɕK�v

// �}�N����`
#define SCREEN_WIDTH	(1280)						// �E�B���h�E�̕�
#define SCREEN_HEIGHT	(720)						// �E�B���h�E�̍���
#define CLASS_NAME			"WindowClass"			// �E�B���h�E�N���X�̖��O
#define WINDOW_NAME			"C++�Q�[������"			// �E�B���h�E�̖��O

// �f�o�b�Onew
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

// �v���g�^�C�v�錾
int GetFPS(void);						// FPS�J�E���^�[�擾
float GetWorldDeltaSeconds(void);		// �t���[���Ԃ̕b��

#endif
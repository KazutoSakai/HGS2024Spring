//*********************************************
//
// �V�[�����(SceneBase.h)
// Author : Junichi Uchiyama
//
//*********************************************

#ifndef _SCENEBASE_H_
#define _SCENEBASE_H_

#include "main.h"
#include "view.h"

/// <summary>
/// �V�[�����
/// </summary>
class CSceneBase
{
public:
	//---------------------
	// public Method
	CSceneBase() {}					// �R���X�g���N�^
	virtual ~CSceneBase() {}		// �f�X�g���N�^

	virtual HRESULT Init() = 0;		// ������
	virtual void Uninit() = 0;		// �j��
	virtual void Update() = 0;		// �X�V
	virtual void Draw() = 0;		// �`��

};

#endif
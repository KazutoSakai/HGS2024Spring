//*********************************************
//
// �Q�[�����U���g(SceneResult.h)
// Author : Junichi Uchiyama
//
//*********************************************

#ifndef _SCENERESULT_H_
#define _SCENERESULT_H_

#include "main.h"

#include "SceneBase.h"

/// <summary>
/// �Q�[���^�C�g����ʊǗ�
/// </summary>
class CSceneResult : public CSceneBase
{
public:
	//---------------------
	// public Method
	CSceneResult() {};
	~CSceneResult() override {};

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

private:


};

#endif
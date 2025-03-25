//*********************************************
//
// �V�[���̐ؑւ�Ǘ�(SceneManager.h)
// Author : Junichi Uchiyama
//
//*********************************************

#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_

#include "SceneBase.h"

class CSceneManager
{
public:
	//---------------------
	// enum

	// �V�[���̎�ށi��ʂ��؂�ւ����́j
	enum class SceneType
	{
		Title,
		Game,
		Result,
		Ranking,

		Max
	};

	//---------------------
	// default
	CSceneManager();
	~CSceneManager();

	//---------------------
	// Method
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
	void ChangeScene(SceneType sceneType, bool killObjects);

private:
	//---------------------
	// Member
	CSceneBase* m_pScene;		// ���݂̃C���X�^���X
	SceneType m_type;			// ���݂̃V�[��

	//---------------------
	// Method
	void ReleaseScene();		// �V�[����Uninit���Ăяo���ď�����

};

#endif
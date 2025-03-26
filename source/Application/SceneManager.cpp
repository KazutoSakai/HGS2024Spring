//*********************************************
//
// �V�[���̐ؑւ�Ǘ�(SceneManager.cpp)
// Author : Junichi Uchiyama
//
//*********************************************

#include "SceneManager.h"

#include "SceneTitle.h"
#include "SceneResult.h"
#include "SceneGame.h"
#include "SceneRanking.h"

#include "object.h"

/// <summary>
/// ������
/// </summary>
CSceneManager::CSceneManager() : m_pScene(nullptr), 
								m_type(SceneType::Title)
{

}

/// <summary>
/// ���
/// </summary>
CSceneManager::~CSceneManager()
{
	if (m_pScene != nullptr)
		delete m_pScene;
}

/// <summary>
/// �����ݒ�
/// </summary>
/// <returns></returns>
HRESULT CSceneManager::Init()
{
	// �f�t�H���g�̉��
	SceneType defaultType = SceneType::Game;

	ChangeScene(defaultType, false);

	return S_OK;
}

/// <summary>
/// �������
/// </summary>
void CSceneManager::Uninit()
{
	ReleaseScene();
}

/// <summary>
/// �V�[���̍X�V��t�F�[�h�Ǘ�
/// </summary>
void CSceneManager::Update()
{
	// �t�F�[�h����
	// TODO:

	if (m_pScene != nullptr)
	{
		m_pScene->Update();
	}
}

/// <summary>
/// �V�[���̕`�揈��
/// </summary>
void CSceneManager::Draw()
{
	if (m_pScene != nullptr)
	{
		m_pScene->Draw();
	}
}

/// <summary>
/// �V�[���ύX
/// </summary>
/// <param name="sceneType">�J�ڐ�</param>
void CSceneManager::ChangeScene(SceneType sceneType, bool killObjects)
{
	// �㏈��
	ReleaseScene();

	// �I�u�W�F�N�g��j������
	if (killObjects)
		CObject::ReleaseAll();

	// �w��ł��邩����
	switch (sceneType)
	{
	case CSceneManager::SceneType::Title:
		m_pScene = DBG_NEW CSceneTitle();
		break;
	case CSceneManager::SceneType::Game:
		m_pScene = DBG_NEW CSceneGame();
		break;
	case CSceneManager::SceneType::Result:
		m_pScene = DBG_NEW CSceneResult();
		break;
	case CSceneManager::SceneType::Ranking:
		m_pScene = DBG_NEW CSceneRanking();
		break;
	default:
		assert(false && "SceneManager::ChangeScene sceneType is default.");
		break;
	}

	// �����ݒ�
	if (m_pScene != nullptr)
	{
		m_pScene->Init();
	}
}

/// <summary>
/// �V�[����Uninit���Ăяo���ď�����
/// </summary>
void CSceneManager::ReleaseScene()
{
	if (m_pScene != nullptr)
	{
		m_pScene->Uninit();
		delete m_pScene;
		m_pScene = nullptr;
	}
}
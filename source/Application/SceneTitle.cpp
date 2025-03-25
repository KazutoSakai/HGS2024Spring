//*********************************************
//
// �Q�[���^�C�g����ʊǗ�(SceneTitle.cpp)
// Author : Junichi Uchiyama
//
//*********************************************

#include "SceneTitle.h"
#include "application.h"

#include "object2D.h"
#include "texture.h"

/// <summary>
/// ������
/// </summary>
/// <returns></returns>
HRESULT CSceneTitle::Init()
{
	//----------------------------
	// �T���v���R�[�h

	// �|���S�������@���p���ł����p�\�BCObject�N���X�ɓo�^�B
	auto obj = CObject2D::Create();
	// �ʒu�ݒ�B��_�͒��S���f�t�H�B
	obj->SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
	// (x, y) = (���A�c)
	obj->SetSize(D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT));
	// �e�N�X�`���ǂݍ��݁i�����CApplication�j
	auto pTex = CApplication::GetInstance()->GetTexture();
	int texId = pTex->LoadTexture("data/sample/texture/texture002.jpg");
	// �o�C���h
	obj->BindTexture(pTex->GetTexture(texId));

	return S_OK;
}

/// <summary>
/// ���
/// </summary>
void CSceneTitle::Uninit()
{

}

/// <summary>
/// �X�V
/// </summary>
void CSceneTitle::Update()
{
	// ����L�[
	if (CApplication::GetInstance()->GetInput()->GetTrigger(CInputManager::InputType::Decide_A))
	{
		CApplication::GetInstance()->GetScene()->ChangeScene(CSceneManager::SceneType::Game, true);
	}
}

/// <summary>
/// �`��
/// </summary>
void CSceneTitle::Draw()
{

}
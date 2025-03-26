//*********************************************
//
// �Q�[�����C����ʊǗ�(SceneGame.cpp)
// Author : Junichi Uchiyama
//
//*********************************************

#include "SceneGame.h"
#include "application.h"

#include "object2D.h"
#include "texture.h"
#include "effect.h"

#include "objectX.h"

#include "input.h"

CObject2D* obj2D;
CObjectX* objX;

/// <summary>
/// ������
/// </summary>
/// <returns></returns>
HRESULT CSceneGame::Init()
{
	//----------------------------
	// �T���v���R�[�h

	// �|���S�������@���p���ł����p�\�BCObject�N���X�ɓo�^�B
	obj2D = CObject2D::Create(CObject::Priority::Character);
	// �ʒu�ݒ�B��_�͒��S���f�t�H�B
	obj2D->SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
	// (x, y) = (���A�c)
	obj2D->SetSize(D3DXVECTOR2(100, 100));
	// �e�N�X�`���ǂݍ��݁i�����CApplication�j
	auto pTex = CApplication::GetInstance()->GetTexture();
	int texId = pTex->LoadTexture("data/sample/texture/player001.png");
	// �o�C���h
	obj2D->BindTexture(pTex->GetTexture(texId));

	// X�t�@�C�����f������
	objX = CObjectX::Create(D3DXVECTOR3(0, 0, 0), "data/sample/model/chara/01_head.x");

	return S_OK;
}

/// <summary>
/// ���
/// </summary>
void CSceneGame::Uninit()
{

}

/// <summary>
/// �X�V
/// </summary>
void CSceneGame::Update()
{
	//----------------------------
	// �T���v���R�[�h
	auto pInput = CApplication::GetInstance()->GetInput();
	{
		auto pos = obj2D->GetPos();
		if (pInput->GetPress(CInputManager::InputType::Move_Up))
			pos.y -= 2.0f;
		if (pInput->GetPress(CInputManager::InputType::Move_Down))
			pos.y += 2.0f;
		if (pInput->GetPress(CInputManager::InputType::Move_Left))
			pos.x -= 2.0f;
		if (pInput->GetPress(CInputManager::InputType::Move_Right))
			pos.x += 2.0f;
		obj2D->SetPos(pos);

		// �G�t�F�N�g�i�R���X�g���N�^�ŕ`�揇��ݒ肵�Ă���j
		auto pEffect = CEffect::Create(pos, D3DCOLOR_ARGB(255, 255, 255, 255), 10);
		pEffect->SetSize(D3DXVECTOR2(100.0f, 100.0f));
	}

	{
		auto pos = objX->GetPos();
		if (pInput->GetPress(CInputManager::InputType::Move_Up))
			pos.y += 2.0f;
		if (pInput->GetPress(CInputManager::InputType::Move_Down))
			pos.y -= 2.0f;
		if (pInput->GetPress(CInputManager::InputType::Move_Left))
			pos.x -= 2.0f;
		if (pInput->GetPress(CInputManager::InputType::Move_Right))
			pos.x += 2.0f;
		objX->SetPos(pos);
	}
	

	// ����L�[
	if (CApplication::GetInstance()->GetInput()->GetTrigger(CInputManager::InputType::Decide_A))
	{
		CApplication::GetInstance()->GetScene()->ChangeScene(CSceneManager::SceneType::Result, true);
	}
}

/// <summary>
/// �`��
/// </summary>
void CSceneGame::Draw()
{

}
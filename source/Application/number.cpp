//*********************************************
//
// ����(number.cpp)
// Author : Junichi Uchiyama
//
//*********************************************

#include "number.h"
#include "application.h"
#include "renderer.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
CNumber::CNumber(Priority priority) : CObject2D(priority)
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CNumber::~CNumber()
{

}

/// <summary>
/// ������
/// </summary>
/// <returns></returns>
HRESULT CNumber::Init()
{
	CObject2D::Init();

	// �e�N�X�`��
	auto pTex = CApplication::GetInstance()->GetTexture();
	int id = pTex->LoadTexture("data/sample/texture/number002.png");
	CObject2D::BindTexture(pTex->GetTexture(id));

	return S_OK;
}

/// <summary>
/// ���
/// </summary>
void CNumber::Uninit()
{
	CObject2D::Uninit();
}

/// <summary>
/// �X�V
/// </summary>
void CNumber::Update()
{
	CObject2D::Update();
}

/// <summary>
/// �`��
/// </summary>
void CNumber::Draw()
{
	CObject2D::Draw();
}

/// <summary>
/// ����
/// </summary>
/// <param name="pos"></param>
/// <returns></returns>
CNumber* CNumber::Create(const D3DXVECTOR3& pos)
{
	CNumber* pNum = nullptr;

	pNum = DBG_NEW CNumber();
	pNum->Init();
	pNum->SetPos(pos);

	return pNum;
}

/// <summary>
/// �`�悷�鐔����ݒ�
/// </summary>
/// <param name="num"></param>
void CNumber::SetNumber(int num)
{
	TEXTURE_UV uv = GetUV();
	uv.leftU = (1.0f / 10) * num;
	uv.rightU = (1.0f / 10) * (num + 1);
	SetUV(uv);

	CObject2D::UpdateVertex();
}
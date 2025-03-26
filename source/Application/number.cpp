//*********************************************
//
// 数字(number.cpp)
// Author : Junichi Uchiyama
//
//*********************************************

#include "number.h"
#include "application.h"
#include "renderer.h"

/// <summary>
/// コンストラクタ
/// </summary>
CNumber::CNumber(Priority priority) : CObject2D(priority)
{

}

/// <summary>
/// デストラクタ
/// </summary>
CNumber::~CNumber()
{

}

/// <summary>
/// 初期化
/// </summary>
/// <returns></returns>
HRESULT CNumber::Init()
{
	CObject2D::Init();

	// テクスチャ
	auto pTex = CApplication::GetInstance()->GetTexture();
	int id = pTex->LoadTexture("data/sample/texture/number002.png");
	CObject2D::BindTexture(pTex->GetTexture(id));

	return S_OK;
}

/// <summary>
/// 解放
/// </summary>
void CNumber::Uninit()
{
	CObject2D::Uninit();
}

/// <summary>
/// 更新
/// </summary>
void CNumber::Update()
{
	CObject2D::Update();
}

/// <summary>
/// 描画
/// </summary>
void CNumber::Draw()
{
	CObject2D::Draw();
}

/// <summary>
/// 生成
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
/// 描画する数字を設定
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
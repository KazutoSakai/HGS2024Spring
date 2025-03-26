
#include "Player.h"
#include "application.h"

CPlayer::CPlayer()
{

}

HRESULT CPlayer::Init()
{
	CObject2D::Init();

	// 位置設定。基準点は中心がデフォ。
	SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT / 5 * 4, 0.0f));
	// (x, y) = (横、縦)
	SetSize(D3DXVECTOR2(200, 32));

	return S_OK;
}

void CPlayer::Uninit()
{
	CObject2D::Uninit();
}

void CPlayer::Update()
{
	auto pInput = CApplication::GetInstance()->GetInput();

	auto pos = GetPos();
	if (pInput->GetPress(CInputManager::InputType::Move_Left) || 
		pInput->GetKeyboard()->GetPress(DIK_LEFT))
		pos.x -= MOVE_POWER;
	if (pInput->GetPress(CInputManager::InputType::Move_Right) ||
		pInput->GetKeyboard()->GetPress(DIK_RIGHT))
		pos.x += MOVE_POWER;
	SetPos(pos);
	
	CObject2D::Update();
}

void CPlayer::Draw()
{
	CObject2D::Draw();
}

CPlayer* CPlayer::Create()
{
	CPlayer* p = DBG_NEW CPlayer();

	p->Init();

	return p;
}
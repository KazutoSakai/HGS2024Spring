
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
	SetSize(D3DXVECTOR2(160, 32));

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

	// 入力移動
	if (pInput->GetPress(CInputManager::InputType::Move_Left) || 
		pInput->GetKeyboard()->GetPress(DIK_LEFT))
		pos.x -= MOVE_POWER;
	if (pInput->GetPress(CInputManager::InputType::Move_Right) ||
		pInput->GetKeyboard()->GetPress(DIK_RIGHT))
		pos.x += MOVE_POWER;

	// 移動制限
	auto sizeHalfX = GetSize().x / 2.0f;
	auto sizeHalfY = GetSize().y / 2.0f;
	if (pos.x + sizeHalfX >= SCREEN_WIDTH - CApplication::SCREEN_SIDE_WIDTH)
		pos.x = SCREEN_WIDTH - CApplication::SCREEN_SIDE_WIDTH - sizeHalfX;
	else if (pos.x - sizeHalfX <= CApplication::SCREEN_SIDE_WIDTH)
		pos.x = CApplication::SCREEN_SIDE_WIDTH + sizeHalfX;

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
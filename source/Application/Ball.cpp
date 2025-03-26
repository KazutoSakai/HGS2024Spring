
#include "Ball.h"
#include "application.h"

#include "BlockManager.h"
#include "collision.h"
#include "Player.h"

CBall::CBall()
{

}

HRESULT CBall::Init()
{
	CObject2D::Init();

	// �ʒu�ݒ�B��_�͒��S���f�t�H�B
	SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT / 5 * 4, 0.0f));
	// (x, y) = (���A�c)
	SetSize(D3DXVECTOR2(32, 32));

	m_move = D3DXVECTOR3(MOVE_POWER, MOVE_POWER, 0.0f);

	// �e�N�X�`��
	auto pTex = CApplication::GetInstance()->GetTexture();
	int id = pTex->LoadTexture("data/sample/texture/bullet_64.png");
	BindTexture(pTex->GetTexture(id));

	return S_OK;
}

void CBall::Uninit()
{
	CObject2D::Uninit();
}

void CBall::Update()
{
	// �ړ�
	auto pos = GetPos();

	pos += m_move;

	// ����
	D3DXVECTOR2 center = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	const int wHalf = CApplication::SCREEN_GAME_WIDTH / 2;
	if (pos.x >= center.x + wHalf || pos.x <= center.x - wHalf)
		m_move.x *= -1.0f;
	else if (pos.y <= 0.0f || pos.y >= SCREEN_HEIGHT)
		m_move.y *= -1.0f;

	// �u���b�N�Ƃ̓����蔻��i���j
	{
		D3DXVECTOR3 outDir = m_move;	// �R�s�[
		if (CBlockManager::GetInstance()->CollisionBlock(pos, GetSize(), &outDir))
		{
			if (outDir.x > 0)
				m_move.x = MOVE_POWER;
			else if (outDir.x < 0)
				m_move.x = -MOVE_POWER;

			if (outDir.y > 0)
				m_move.y = MOVE_POWER;
			else if (outDir.y < 0)
				m_move.y = -MOVE_POWER;

			//// �������i�ړ������ɑ΂��Ē��S����㉺�ǂ���œ������������l���ł��Ă��Ȃ��j
			//if (outDir.x > 0 && m_move.x < 0 || outDir.x < 0 && m_move.x > 0)
			//	m_move.x *= -1.0f;
			//if (outDir.y > 0 && m_move.y < 0 || outDir.y < 0 && m_move.y > 0)
			//	m_move.y *= -1.0f;

			// �@���i���������������j
			//m_move = outDir;
		}
	}

	// �v���C���[�Ƃ̓����蔻��
	{
		auto pl = static_cast<CPlayer*>(GetObj(CObject::Priority::Default, m_PlayerID));
		if (pl != nullptr)
		{
			const auto& pPos = pl->GetPos();
			auto pSize = pl->GetSize();
			CollisionSquare sq =
			{
				pPos.x, pPos.y,
				pSize.x, pSize.y,
				0.0f,
			};

			CollisionCircle cr =
			{
				pos.x, pos.y, GetSize().x
			};

			D3DXVECTOR2 BVsPOut = D3DXVECTOR2(m_move.x, m_move.y);	// �R�s�[
			if (CollisionSqVsCircleReflection(sq, cr, &BVsPOut))
			{
				if (BVsPOut.x > 0)
					m_move.x = MOVE_POWER;
				else if (BVsPOut.x < 0)
					m_move.x = -MOVE_POWER;

				if (BVsPOut.y > 0)
					m_move.y = MOVE_POWER;
				else if (BVsPOut.y < 0)
					m_move.y = -MOVE_POWER;
			}
		}
	}

	SetPos(pos);

	CObject2D::Update();
}

void CBall::Draw()
{
	CObject2D::Draw();
}

CBall* CBall::Create()
{
	CBall* p = DBG_NEW CBall();

	p->Init();

	return p;
}
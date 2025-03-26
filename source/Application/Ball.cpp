
#include "Ball.h"
#include "application.h"

#include "BlockManager.h"
#include "collision.h"
#include "Player.h"

#include "SceneGame.h"

CBall::CBall()
{
	isVsPlayerDoneCounter = false;
}

HRESULT CBall::Init()
{
	CObject2D::Init();

	// �ʒu
	SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 6 * 4, 0.0f));

	// (x, y) = (���A�c)
	SetSize(D3DXVECTOR2(32, 32));

	m_move = D3DXVECTOR3(MOVE_POWER, -MOVE_POWER, 0.0f);

	// �{�[���p�̃T�E���h�C���X�^���X�쐬(��)
	m_pBallSound = CApplication::GetInstance()->GetSound();

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

	SetPos(pos);

	//-----------------------------------
	// �����蔻��

	//-----------------------------------
	// ��ʊO�Ƃ̐���

	if (pos.x >= SCREEN_WIDTH - CApplication::SCREEN_SIDE_WIDTH || pos.x <= CApplication::SCREEN_SIDE_WIDTH)
		m_move.x *= -1.0f;
	else if (pos.y <= 0.0f)
	{
		m_move.y *= -1.0f;
	}
	else if (pos.y >= SCREEN_HEIGHT)
	{
		// ��ʂ̈�ԉ��ɓ�������

		// ���X�^�[�g
		auto game = static_cast<CSceneGame*>(CApplication::GetInstance()->GetScene()->GetCurrentScene());
		game->Resporn();

		// �폜
		Uninit();
		return;
	}

	//-----------------------------------
	// �u���b�N�Ƃ̓����蔻��i���j
	{
		D3DXVECTOR3 outDir = m_move;	// �R�s�[
		// ��������
		if (CBlockManager::GetInstance()->CollisionBlock(pos, GetSize(), &outDir))
		{
			// �T�E���h�Đ�
			m_pBallSound->Play(CSound::SE_HIT);

			// �ړ�������ς���
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

	//-----------------------------------
	// �v���C���[�Ƃ̓����蔻��
	if (isVsPlayerDoneCounter == 0)
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

			// ��������
			if (CollisionSqVsCircleReflection(sq, cr, &BVsPOut))
			{
				// �T�E���h�Đ�
				m_pBallSound->Play(CSound::SE_SHOT);

				// �ړ�������ς���
				if (BVsPOut.x > 0)
					m_move.x = MOVE_POWER;
				else if (BVsPOut.x < 0)
					m_move.x = -MOVE_POWER;

				if (BVsPOut.y > 0)
					m_move.y = MOVE_POWER;
				else if (BVsPOut.y < 0)
					m_move.y = -MOVE_POWER;

				// ������Ȃ����Ԃ�����
				isVsPlayerDoneCounter = 10;
			}

		}
	}
	else if (isVsPlayerDoneCounter > 0)
	{
		isVsPlayerDoneCounter--;
	}


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
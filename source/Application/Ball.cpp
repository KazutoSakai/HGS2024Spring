
#include "Ball.h"
#include "application.h"

#include "BlockManager.h"
#include "collision.h"
#include "Player.h"

#include "SceneGame.h"
#include "ScoreManager.h"
#include "RateBallManager.h"

CBall::CBall()
{
	m_move = D3DXVECTOR3(0, 0, 0);
	m_pBallSound = nullptr;
	m_PlayerID = 0;
	isVsPlayerDoneCounter = false;

	m_NumRate = 0;
	for (int i = 0; i < RATE_MAX; i++)
		m_NumRateID[i] = 0;
}

HRESULT CBall::Init()
{
	CObject2D::Init();

	// 位置
	SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 6 * 4, 0.0f));

	// (x, y) = (横、縦)
	SetSize(D3DXVECTOR2(32, 32));

	m_move = D3DXVECTOR3(MOVE_POWER, -MOVE_POWER, 0.0f);

	// ボール用のサウンドインスタンス作成(堺)
	m_pBallSound = CApplication::GetInstance()->GetSound();

	// テクスチャ
	auto pTex = CApplication::GetInstance()->GetTexture();
	m_NumRateID[0] = pTex->LoadTexture("data/sample/texture/bullet_64.png");
	m_NumRateID[1] = pTex->LoadTexture("data/sample/texture/mag_2.png");
	m_NumRateID[2] = pTex->LoadTexture("data/sample/texture/mag_3.png");
	m_NumRateID[3] = pTex->LoadTexture("data/sample/texture/mag_4.png");
	m_NumRateID[4] = pTex->LoadTexture("data/sample/texture/mag_5.png");
	m_NumRateID[5] = pTex->LoadTexture("data/sample/texture/mag_6.png");
	m_NumRateID[6] = pTex->LoadTexture("data/sample/texture/mag_7.png");
	m_NumRateID[7] = pTex->LoadTexture("data/sample/texture/mag_8.png");
	m_NumRateID[8] = pTex->LoadTexture("data/sample/texture/mag_9.png");
	BindTexture(pTex->GetTexture(m_NumRateID[0]));
	m_NumRate = DEFAULT_RATE;		// 1倍スタート


	return S_OK;
}

void CBall::Uninit()
{
	CObject2D::Uninit();
}

void CBall::Update()
{
	// リザルト中は飛ばす
	auto game = static_cast<CSceneGame*>(CApplication::GetInstance()->GetScene()->GetCurrentScene());
	if (game->IsGameRun() == false)
	{
		return;
	}

	// 移動
	auto pos = GetPos();

	pos += m_move;

	SetPos(pos);

	//-----------------------------------
	// 当たり判定

	//-----------------------------------
	// 画面外との制限

	if (pos.x >= SCREEN_WIDTH - CApplication::SCREEN_SIDE_WIDTH || pos.x <= CApplication::SCREEN_SIDE_WIDTH)
		m_move.x *= -1.0f;
	else if (pos.y <= 0.0f)
	{
		m_move.y *= -1.0f;
	}
	else if (pos.y >= SCREEN_HEIGHT)
	{
		// 画面の一番下に当たった

		// リスタート
		auto game = static_cast<CSceneGame*>(CApplication::GetInstance()->GetScene()->GetCurrentScene());
		game->Resporn();

		// 削除
		Uninit();
		return;
	}

	//-----------------------------------
	// ブロックとの当たり判定（仮）
	{
		D3DXVECTOR3 outDir = m_move;	// コピー
		// 当たった
		if (CBlockManager::GetInstance()->CollisionBlock(pos, GetSize(), &outDir))
		{
			// サウンド再生
			m_pBallSound->Play(CSound::SE_HIT);

			// スコアを加算する（倍率処理の上で）
			CScoreManager::GetInstance()->AddScore(100 * m_NumRate);

			// 倍率を上げてテクスチャ設定（1〜9なので-1してます）
			m_NumRate++;
			if (m_NumRate >= RATE_MAX)
			{
				CRateBallManager::GetInstance()->Regist(m_NumRate);
				m_NumRate = DEFAULT_RATE;
			}
			auto pTex = CApplication::GetInstance()->GetTexture();
			BindTexture(pTex->GetTexture(m_NumRateID[m_NumRate - 1]));

			// 移動方向を変える
			if (outDir.x > 0)
				m_move.x = MOVE_POWER;
			else if (outDir.x < 0)
				m_move.x = -MOVE_POWER;

			if (outDir.y > 0)
				m_move.y = MOVE_POWER;
			else if (outDir.y < 0)
				m_move.y = -MOVE_POWER;

			//// 仮処理（移動方向に対して中心から上下どちらで当たったかを考慮できていない）
			//if (outDir.x > 0 && m_move.x < 0 || outDir.x < 0 && m_move.x > 0)
			//	m_move.x *= -1.0f;
			//if (outDir.y > 0 && m_move.y < 0 || outDir.y < 0 && m_move.y > 0)
			//	m_move.y *= -1.0f;

			// 法線（挙動がおかしい）
			//m_move = outDir;
		}
	}

	//-----------------------------------
	// プレイヤーとの当たり判定
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

			D3DXVECTOR2 BVsPOut = D3DXVECTOR2(m_move.x, m_move.y);	// コピー

			// 当たった
			if (CollisionSqVsCircleReflection(sq, cr, &BVsPOut))
			{
				// サウンド再生
				m_pBallSound->Play(CSound::SE_SHOT);

				// 倍率があがっていたらを登録して戻す
				if (m_NumRate > DEFAULT_RATE)
				{
					CRateBallManager::GetInstance()->Regist(m_NumRate);
					m_NumRate = DEFAULT_RATE;
				}
				m_NumRate = DEFAULT_RATE;
				auto pTex = CApplication::GetInstance()->GetTexture();
				BindTexture(pTex->GetTexture(m_NumRateID[m_NumRate - 1]));

				// 移動方向を変える
				if (BVsPOut.x > 0)
					m_move.x = MOVE_POWER;
				else if (BVsPOut.x < 0)
					m_move.x = -MOVE_POWER;

				if (BVsPOut.y > 0)
					m_move.y = MOVE_POWER;
				else if (BVsPOut.y < 0)
					m_move.y = -MOVE_POWER;

				// 当たらない時間をつくる
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
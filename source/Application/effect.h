//*********************************************
//
// エフェクト(effect.h)
// Author : Junichi Uchiyama
//
//*********************************************

#include "object2D.h"

class CEffect : public CObject2D
{
public:
	CEffect(Priority priority = Priority::Effect_Low);	// コンストラクタ
	~CEffect() override;								// デストラクタ

	HRESULT Init() override;							// 初期化
	void Uninit() override;								// 解放
	void Update() override;								// 更新
	void Draw() override;								// 描画

	static HRESULT Load();								// 読込
	static void UnLoad();								// 破棄
	static CEffect* Create(const D3DXVECTOR3& pos, const D3DXCOLOR& col, int life);		// 生成

	int GetLife();										// 寿命取得
	void SetLife(int life);								// 寿命設定

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;				// テクスチャ

	int m_life;											// 寿命
};
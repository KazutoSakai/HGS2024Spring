//*********************************************
//
// ポリゴン描画(object2D.h)
// Author : Junichi Uchiyama
//
//*********************************************

#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_

#include "object.h"

#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)	// 頂点フォーマット

// 頂点情報[2D]
typedef struct
{
	D3DXVECTOR3 pos;		// 頂点座標
	float rhw;				// 座標変換用係数（1.0f)
	D3DCOLOR col;			// 頂点カラー
	D3DXVECTOR2 tex;		// テクスチャ座標
}VERTEX_2D;

// テクスチャ座標管理
typedef struct
{
	float leftU;		// 左上U
	float topV;			// 右上V
	float rightU;		// 左下U
	float bottomV;		// 右下V
}TEXTURE_UV;

/// <summary>
/// 2Dオブジェクト
/// </summary>
class CObject2D : public CObject
{
public:
	//---------------------
	// enum

	// アンカーポイントを設定
	enum class POSTYPE
	{
		Center,
		Under,
		LeftTop,

		Max
	};

	//---------------------
	// public Method
	CObject2D(CObject::Priority priority = Priority::Default);		// コンストラクタ
	~CObject2D() override;		// デストラクタ

	HRESULT Init() override;		// 初期化
	void Uninit() override;			// 終了
	void Update() override;			// 更新
	void Draw() override;			// 描画
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);		// テクスチャ反映
	void UpdateVertex();			// 頂点更新

	//---------------------
	// static Method
	static CObject2D* Create(CObject::Priority priority = Priority::Default);

	//---------------------
	// Getter
	const D3DXVECTOR2& GetSize() const;			// サイズ取得
	void SetSize(const D3DXVECTOR2& size);		// サイズ設定

	const TEXTURE_UV& GetUV() const;			// テクスチャ座標取得
	void SetUV(const TEXTURE_UV& uv);			// テクスチャ座標設定

	const POSTYPE& GetPosType() const;			// 頂点位置の設定方法
	void SetPosType(const POSTYPE& type);		// 頂点位置の設定方法

private:
	//---------------------
	// private Member
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuf;		// 頂点バッファ
	LPDIRECT3DTEXTURE9 m_pTexture;			// テクスチャ

	D3DXVECTOR2 m_size;						// 縦横サイズ
	TEXTURE_UV m_uv;						// テクスチャ座標
	POSTYPE m_posType;						// 頂点位置の設定方法
};

#endif
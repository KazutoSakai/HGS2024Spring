//*********************************************
//
// 3Dオブジェクト(object3D.h)
// Author : Junichi Uchiyama
//
//*********************************************

#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

#include "object.h"

#define FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)	// 座標、法線、カラー、テクスチャ

/// <summary>
/// 頂点情報3D
/// </summary>
typedef struct
{
	D3DXVECTOR3 pos;		// 頂点座標
	D3DXVECTOR3 nor;		// 法線
	DWORD col;				// 頂点カラー
	D3DXVECTOR2 tex;		// テクスチャ座標
}VERTEX_3D;

/// <summary>
/// 3Dオブジェクトに必要な情報を持った抽象クラス
/// </summary>
class CObject3D : public CObject
{
public:
	//---------------------
	// public Method
	CObject3D(Priority priority = Priority::Default);		// コンストラクタ
	~CObject3D() override;									// デストラクタ

	HRESULT Init() = 0;										// 初期化（純粋化）
	void Uninit() override;									// 解放
	void Update() override;									// 更新
	virtual void Draw() = 0;								// 描画
	void UpdateWorldMatrix();								// ワールド行列作成

	//---------------------
	// Getter Setter
	const D3DXMATRIX& GetWorldMat() const;		// ワールドマトリクス取得
	void SetWorldMat(const D3DXMATRIX& mat);	// ワールドマトリクス設定

	const D3DXMATRIX& GetRotMat() const;		// 回転行列の取得

protected:
	//---------------------
	// protected Method（オーバーライド可能）
	virtual void UpdateScaling(D3DXMATRIX* pOut);
	virtual void UpdateRotation(D3DXMATRIX* pOut);
	virtual void UpdateTranslation(D3DXMATRIX* pOut);

private:
	//---------------------
	// private Method
	D3DXMATRIX m_WorldMat;	// ワールドマトリクス
	D3DXMATRIX m_RotMat;	// 回転行列
};

#endif
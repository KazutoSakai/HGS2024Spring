//*********************************************
//
// オブジェクトX(objectX.h)
// Author : Junichi Uchiyama
//
//*********************************************

#ifndef _OBJECTX_H_
#define _OBJECTX_H_

#include "object3D.h"

/// <summary>
/// Xファイルを読み込み描画する
/// </summary>
class CObjectX : public CObject3D
{
public:
	//---------------------
	// public Method
	CObjectX(Priority priority = Priority::Default);		// コンストラクタ
	~CObjectX() override;									// デストラクタ

	HRESULT Init() override;								// 初期化
	void Uninit() override;									// 解放
	void Update() override;									// 更新
	void Draw() override;									// 描画
	HRESULT LoadXFile(const char* filename);				// Xファイル読込
	void SetColor(const D3DXCOLOR& col) override;			// カラーを上書きする
	void BindTexture(LPDIRECT3DTEXTURE9 pTex);				// テクスチャを反映

	//---------------------
	// static Method
	static CObjectX* Create(const D3DXVECTOR3& pos, const char* filename);

	//---------------------
	// Getter Setter
	D3DXVECTOR3& GetLocalMin() { return m_vtxLocalMin; }
	D3DXVECTOR3& GetLocalMax() { return m_vtxLocalMax; }

private:
	//---------------------
	// private Member
	LPD3DXMESH m_pMesh;				// メッシュ情報
	LPD3DXBUFFER m_pMaterialBuf;	// マテリアル情報
	DWORD m_MaterialNum;			// マテリアル数

	D3DXVECTOR3 m_vtxLocalMin;		// 頂点最小座標
	D3DXVECTOR3 m_vtxLocalMax;		// 頂点最大座標

	LPDIRECT3DTEXTURE9 m_pTexture;	// テクスチャ
};

#endif
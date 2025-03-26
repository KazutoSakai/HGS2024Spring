//*********************************************
//
// オブジェクト(object.h)
// Author : Junichi Uchiyama
//
//*********************************************

#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "main.h"
#include "stencil.h"

/// <summary>
/// オブジェクトクラス
/// </summary>
class CObject
{
public:

	//---------------------
	// 定数
	static const int MAX_OBJ = 128;

	//---------------------
	// enum

	// オブジェクトタイプ
	enum ObjType
	{
		DEFAULT,	// 無し
		PLAYER,		// プレイヤー

		MAX,		// 最大数
		INVALID,	// 無効ID
	};

	// 描画優先度
	enum Priority
	{
		View = 0,
		UltraLow,
		Low,
		Default = 3,
		Object,
		Effect_Low,
		Character,
		Effect_Up,
		UI,

		Max
	};

	//---------------------
	// public Method
	CObject(Priority priority = Priority::Default);		// コンストラクタ
	virtual ~CObject();									// デストラクタ

	virtual HRESULT Init() = 0;							// 初期化
	virtual void Uninit() = 0;							// 破棄（Release()を内部で呼び出すことで削除される）
	virtual void Update() = 0;							// 更新
	virtual void Draw() = 0;							// 描画
	virtual void DebugDraw();							// デバッグ描画

	//---------------------
	// static Method
	static void ReleaseAll();							// 管理オブジェクトの解放
	static void UpdateAll();							// 管理オブジェクトの更新
	static void DrawAll();								// 管理オブジェクトの描画
	static void DrawDebugAll();							// 管理オブジェクトのデバッグ描画
	static CObject* GetObj(Priority priority, int idx);	// オブジェクト取得

	//---------------------
	// Getter
	ObjType GetObjType() const;							// オブジェクトタイプ取得
	void SetObjType(ObjType type);						// オブジェクトを設定

	const D3DXVECTOR3& GetPos() const;					// 座標取得
	void SetPos(const D3DXVECTOR3& pos);				// 座標設定

	const D3DXVECTOR3& GetRot() const;					// 回転取得
	void SetRot(const D3DXVECTOR3& rot);				// 回転設定

	const D3DXVECTOR3& GetScale() const;				// スケール取得
	void SetScale(const D3DXVECTOR3& scale);			// スケール設定
	
	bool IsUpdate();									// 更新するか取得
	void SetIsUpdate(bool flg);							// 更新するか設定

	CStencil::STENCIL_TYPE GetStencilType();			// ステンシルバッファ取得
	void SetStencilType(CStencil::STENCIL_TYPE type);	// ステンシルバッファ設定

	virtual const D3DXCOLOR& GetColor() const;			// カラー取得
	virtual void SetColor(const D3DXCOLOR& col);		// カラー設定

	int GetId();										// ID取得

	void SetFlgManualDelete(bool manual);			// 手動での削除をするか

protected:

	//---------------------
	// protected Method
	void Release();										// 自身を解放

private:
	//---------------------
	// private Member

	static CObject* m_apObject[Priority::Max][MAX_OBJ];	// 管理オブジェクト
	static int m_nNumAll;								// 管理オブジェクト総数
	Priority m_priority;								// 優先順位の番号

	int m_ID;											// 識別番号;
	ObjType m_objType;									// オブジェクトの種類

	D3DXVECTOR3 m_pos;									// 座標
	D3DXVECTOR3 m_rot;									// 回転
	D3DXVECTOR3 m_scale;								// スケール
	D3DXCOLOR m_color;									// カラー

	bool m_IsUpdate;									// 更新処理を行うか否か
	CStencil::STENCIL_TYPE m_StencilBufType;			// ステンシルバッファタイプ

	bool m_FlgManualRelease;							// このフラグをTRUEにすると手動でUninit()関数を呼び出す必要がある
};

#endif
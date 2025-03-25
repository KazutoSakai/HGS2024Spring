//*********************************************
//
// オブジェクト(object.cpp)
// Author : Junichi Uchiyama
//
//*********************************************

#include "object.h"
#include "renderer.h"
#include "application.h"

// 静的メンバ変数
CObject* CObject::m_apObject[CObject::Priority::Max][MAX_OBJ] = {};
int CObject::m_nNumAll = 0;

/// <summary>
/// コンストラクタ
/// </summary>
CObject::CObject(Priority priority) : m_priority(priority), m_ID(-1), m_objType(CObject::ObjType::DEFAULT)
{
	for (int i = 0; i < MAX_OBJ; i++)
	{
		if (m_apObject[priority][i] == nullptr)
		{
			m_apObject[priority][i] = this;	// 自身のポインタを格納
			m_nNumAll++;
			m_ID = i;		// 識別番号を保持
			break;
		}
	}

	assert(m_ID >= 0);

	m_pos = D3DXVECTOR3(0, 0, 0);
	m_rot = D3DXVECTOR3(0, 0, 0);
	m_scale = D3DXVECTOR3(1, 1, 1);		// スケール１
	m_color = 0xffffffff;

	// 更新処理を行うか否か
	m_IsUpdate = true;
	// 手動で削除するかどうか
	m_FlgManualRelease = false;

	m_StencilBufType = CStencil::STENCIL_TYPE::NONE;
}

/// <summary>
/// デストラクタ
/// </summary>
CObject::~CObject()
{

}

/// <summary>
/// デバッグ描画
/// </summary>
void CObject::DebugDraw()
{
	//CApplication::GetInstance()->GetRenderer()->DebugDrawText();
}

/// <summary>
/// 全解放
/// </summary>
void CObject::ReleaseAll()
{
	for (int priority = 0; priority < Priority::Max; priority++)
	{
		for (int i = 0; i < MAX_OBJ; i++)
		{
			if (m_apObject[priority][i] != nullptr && 
				m_apObject[priority][i]->m_FlgManualRelease == false)
			{
				m_apObject[priority][i]->Uninit();
			}
		}
	}
}

/// <summary>
/// 全更新
/// </summary>
void CObject::UpdateAll()
{
	for (int priority = 0; priority < Priority::Max; priority++)
	{
		for (int i = 0; i < MAX_OBJ; i++)
		{
			if (m_apObject[priority][i] != nullptr && m_apObject[priority][i]->m_IsUpdate)
			{
				m_apObject[priority][i]->Update();
			}
		}
	}
}

/// <summary>
/// 全描画
/// </summary>
void CObject::DrawAll()
{
	for (int priority = 0; priority < Priority::Max; priority++)
	{
		for (int i = 0; i < MAX_OBJ; i++)
		{
			if (m_apObject[priority][i] != nullptr)
			{
				// ステンシル描画はチェックしてから
				CStencil::STENCIL_TYPE type = m_apObject[priority][i]->GetStencilType();
				if (type >= CStencil::STENCIL_TYPE::BASE)
				{
					CStencil::Begine(type);
				}

				// 描画
				m_apObject[priority][i]->Draw();

				// ステンシル終了
				CStencil::End();

				// 重なりオブジェクトの場合はもう一度
				if (type == CStencil::STENCIL_TYPE::OVERLAP)
				{
					m_apObject[priority][i]->Draw();
				}
			}
		}
	}
}

void CObject::DrawDebugAll()
{
#ifndef _DEUBG

	for (int priority = 0; priority < Priority::Max; priority++)
	{
		for (int i = 0; i < MAX_OBJ; i++)
		{
			if (m_apObject[priority][i] != nullptr)
			{
				// 描画
				m_apObject[priority][i]->DebugDraw();
			}
		}
	}

#endif
}

/// <summary>
/// オブジェクトタイプを取得
/// </summary>
/// <returns></returns>
CObject::ObjType CObject::GetObjType() const
{
	return m_objType;
}

/// <summary>
/// オブジェクトタイプを設定
/// </summary>
/// <param name="type"></param>
void CObject::SetObjType(CObject::ObjType type)
{
	m_objType = type;
}

/// <summary>
/// オブジェクト取得
/// </summary>
/// <param name="type"></param>
/// <returns></returns>
CObject* CObject::GetObj(Priority priority, int idx)
{
	if (idx >= MAX_OBJ)
	{
		return nullptr;
	}

	return m_apObject[priority][idx];
}

/// <summary>
/// 自身を解放
/// </summary>
void CObject::Release()
{
	int id = m_ID;		// IDを保持
	int priority = m_priority;

	delete m_apObject[priority][id];
	m_apObject[priority][id] = nullptr;

	m_nNumAll--;
}

/// <summary>
/// 座標取得
/// </summary>
/// <returns></returns>
const D3DXVECTOR3& CObject::GetPos() const
{
	return m_pos;
}

/// <summary>
/// 座標設定（基準点はPOSTYPEで設定）
/// </summary>
/// <param name="pos"></param>
void CObject::SetPos(const D3DXVECTOR3& pos)
{
	m_pos = pos;
}

/// <summary>
/// 回転取得
/// </summary>
/// <returns></returns>
const D3DXVECTOR3& CObject::GetRot() const
{
	return m_rot;
}

/// <summary>
/// 回転設定
/// </summary>
/// <param name="pos"></param>
void CObject::SetRot(const D3DXVECTOR3& rot)
{
	m_rot = rot;
}

/// <summary>
/// スケール取得
/// </summary>
/// <returns></returns>
const D3DXVECTOR3& CObject::GetScale() const
{
	return m_scale;
}

/// <summary>
/// スケール設定
/// </summary>
/// <param name="pos"></param>
void CObject::SetScale(const D3DXVECTOR3& scale)
{
	m_scale = scale;
}

/// <summary>
/// 更新するか取得
/// </summary>
/// <returns></returns>
bool CObject::IsUpdate()
{
	return m_IsUpdate;
}

/// <summary>
/// 更新するか設定
/// </summary>
/// <param name="flg"></param>
void CObject::SetIsUpdate(bool flg)
{
	m_IsUpdate = flg;
}

/// <summary>
/// ステンシル取得
/// </summary>
/// <returns></returns>
CStencil::STENCIL_TYPE CObject::GetStencilType()
{
	return m_StencilBufType;
}

/// <summary>
/// ステンシル設定
/// </summary>
/// <param name="type"></param>
void CObject::SetStencilType(CStencil::STENCIL_TYPE type)
{
	m_StencilBufType = type;
}

/// <summary>
/// カラー取得
/// </summary>
/// <returns></returns>
const D3DXCOLOR& CObject::GetColor() const
{
	return m_color;
}

/// <summary>
/// カラー設定
/// </summary>
/// <param name="col"></param>
void CObject::SetColor(const D3DXCOLOR& col)
{
	m_color = col;
}

/// <summary>
/// ID取得
/// </summary>
/// <returns></returns>
int CObject::GetId()
{
	return m_ID;
}

/// <summary>
/// 手動での削除をするか
/// </summary>
/// <param name="manual"></param>
void CObject::SetFlgManualDelete(bool manual)
{
	m_FlgManualRelease = manual;
}
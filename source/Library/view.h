//*********************************************
//
// 3Dビュー制御(view.h)
// Author : Junichi Uchiyama
//
//*********************************************

#ifndef _VIEW_H_
#define _VIEW_H_

#include "object.h"

class CView : public CObject
{
public:
	//---------------------
	// enum

	// 描画方法の設定
	enum class ViewSetting
	{
		Perspective=0,		// 透視射影変換
		Ortho,				// 並行投影変換

		Max,
	};

	//---------------------
	// public Method
	CView(Priority priority = Priority::View);		// コンストラクタ
	~CView() override;								// デストラクタ

	HRESULT Init() override;						// 初期化
	void Uninit() override;							// 解放
	void Update() override;							// 更新
	void Draw() override;							// 描画
	void DebugDraw() override;						// デバッグ描画

	void ShakeCamera(int frame, int mag);			// カメラ揺れを実行する

	//---------------------
	// static Method
	static CView* Create();							// 生成
	
	//---------------------
	// Getter Setter
	const D3DXVECTOR3& GetEye() const;				// 基準点取得
	void SetEye(const D3DXVECTOR3& eye);			// 基準点設定

	const D3DXVECTOR3& GetLookAt() const;			// 基準点取得
	void SetLookAt(const D3DXVECTOR3& look);		// 基準点設定

	const D3DXVECTOR3& GetUp() const;				// 基準点取得
	void SetUp(const D3DXVECTOR3& up);				// 基準点設定

	float GetDistance();							// 距離取得
	void SetDistance(float dist);					// 距離設定

	const D3DXVECTOR3& GetForward() const;			// 前方取得
	const D3DXVECTOR3& GetRight() const;			// 右方向取得

	float GetYaw();									// ヨー取得
	float GetPitch();								// ロール取得

	CObject* GetTargetObj();						// 注視点対象取得
	void SetTargetObj(CObject* pObj);				// 注視点対象設定

	ViewSetting GetViewSetting();					// ビュー変換取得
	void SetViewSetting(ViewSetting setting);		// ビュー変換設定

private:
	//---------------------
	// static Member
	static const int MAX_PARAM = 100;
	static constexpr float ADJUST_Y = 30.0f;

	//---------------------
	// private Member
	D3DXVECTOR3 m_Eye;								// 基準点
	D3DXVECTOR3 m_LookAt;							// 注視点
	D3DXVECTOR3 m_Up;								// 上方向

	D3DXMATRIX m_ProjectionMat;						// 射影変換行列
	D3DXMATRIX m_ViewMat;							// ビュー行列

	D3DXVECTOR3 m_Forward;							// カメラの前方方向
	D3DXVECTOR3 m_Right;							// カメラの
	float m_Distance;

	ViewSetting m_ViewSetting;

	// クォータニオン
	D3DXQUATERNION m_rotQuat;
	float m_yaw;
	float m_pitch;
	float m_rotSpeed;

	// ロックオン
	CObject* m_targetObj;
	D3DXVECTOR3 m_move;

	int m_shakeFrame;
	int m_shakeMagnitude;
};

#endif
//*********************************************
//
// 3Dビュー制御(view.cpp)
// Author : Junichi Uchiyama
//
//*********************************************

#include "view.h"
#include "input.h"
#include "origin_math.h"
#include "application.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="priority">描画優先</param>
CView::CView(Priority priority) : CObject(priority)
{
	m_Eye = D3DXVECTOR3(0, 0, -100);
	m_LookAt = D3DXVECTOR3(0, 0, 0);
	m_Up = D3DXVECTOR3(0, 1, 0);
	m_Forward = D3DXVECTOR3(0, 0, 0);
	m_Right = D3DXVECTOR3(0, 0, 0);
	m_Distance = 300.0f;
	m_ViewSetting = ViewSetting::Perspective;

	D3DXMatrixIdentity(&m_ProjectionMat);
	D3DXMatrixIdentity(&m_ViewMat);

	D3DXQuaternionIdentity(&m_rotQuat);
	m_yaw = 0.0f;
	m_pitch = 0.0f;
	m_rotSpeed = 0.0f;

	m_targetObj = nullptr;
	m_move = D3DXVECTOR3(0, 0, 0);

	m_shakeFrame = 0;
	m_shakeMagnitude = 10;
}

/// <summary>
/// デストラクタ
/// </summary>
CView::~CView()
{

}

/// <summary>
/// 初期化
/// </summary>
/// <returns></returns>
HRESULT CView::Init()
{
	// ビューポート
	auto pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	D3DVIEWPORT9 viewport;
	viewport.X = 0;
	viewport.Y = 0;
	viewport.Width = SCREEN_WIDTH;
	viewport.Height = SCREEN_HEIGHT;
	viewport.MinZ = 0.0f;
	viewport.MaxZ = 1.0f;
	pDevice->SetViewport(&viewport);

	return S_OK;
}

/// <summary>
/// 解放
/// </summary>
void CView::Uninit()
{
	Release();
}

/// <summary>
/// 更新
/// </summary>
void CView::Update()
{
	// 仮カメラ操作
	
	CInputKeyboard* pInput = CApplication::GetInstance()->GetInput()->GetKeyboard();
	D3DXVECTOR3 rot = GetRot();
	const float CAMERA_MOVE = 2.0f;

#if 0
	// カメラ操作
	if (pInput->GetPress(DIK_NUMPAD5))
	{
		m_Distance -= CAMERA_MOVE;
		if (m_Distance <= 15.0f) {
			m_Distance = 15.0f;
		}
	}
	else if (pInput->GetPress(DIK_NUMPAD0)) {
		m_Distance += CAMERA_MOVE;
		if (m_Distance >= 300.0f) {
			m_Distance = 300.0f;
		}
	}
	// カメラ操作
	if (pInput->GetPress(DIK_NUMPAD4))
	{
		rot.y += CalcDegreeToRad(1);
		if (rot.y >= D3DX_PI)
		{
			rot.y -= (D3DX_PI * 2.0f);	// -180 ~ 180
		}
	}
	else if (pInput->GetPress(DIK_NUMPAD6))
	{
		rot.y -= CalcDegreeToRad(1);
		if (rot.y <= -D3DX_PI)
		{
			rot.y += (D3DX_PI * 2.0f);	// -180 ~ 180
		}
	}
	if (pInput->GetPress(DIK_NUMPAD8))
	{
		rot.x += CalcDegreeToRad(1);
		if (rot.x > CalcDegreeToRad(45))
		{
			rot.x = CalcDegreeToRad(45);
		}
	}
	else if (pInput->GetPress(DIK_NUMPAD2))
	{
		rot.x -= CalcDegreeToRad(1);
		if (rot.x < CalcDegreeToRad(-45))
		{
			rot.x = CalcDegreeToRad(-45);
		}
	}
	m_Forward = D3DXVECTOR3(-sinf(-rot.y), 0.0f, cosf(-rot.y));
	m_Right = D3DXVECTOR3(cosf(rot.y), 0.0f, -sinf(rot.y));
	// X座標
	m_Eye.x = m_LookAt.x + sinf(-rot.y) * m_Distance;
	// Y座標
	m_Eye.y = m_LookAt.y + sinf(-rot.x) * m_Distance;
	// Z座標
	// Y軸回転
	float zY = m_LookAt.z - cosf(-rot.y) * m_Distance;
	// X軸回転
	float zX = m_LookAt.z - cosf(-rot.x) * m_Distance;
	m_Eye.z = (zX <= zY) ? zY : zX;
	SetRot(rot);

#endif

#ifdef _DEBUG

	if (CApplication::GetInstance()->GetDebugCamera())
	{
		float dx = 0, dy = 0;
		float mx = 0, my = 0, mz = 0;

		static bool isFPS = false;
		if (isFPS)
		{

		}
		else
		{
			if (pInput->GetPress(DIK_NUMPAD8))
			{
				m_Eye += CAMERA_MOVE * m_LookAt;
			}
			if (pInput->GetPress(DIK_NUMPAD5))
			{
				m_Eye -= CAMERA_MOVE * m_LookAt;
			}
			if (pInput->GetPress(DIK_NUMPAD4))
			{
				m_Eye -= CAMERA_MOVE * D3DXVECTOR3(m_LookAt.z, 0.0f, -m_LookAt.x);
			}
			if (pInput->GetPress(DIK_NUMPAD6))
			{
				m_Eye += CAMERA_MOVE * D3DXVECTOR3(m_LookAt.z, 0.0f, -m_LookAt.x);
			}
			if (pInput->GetPress(DIK_NUMPAD7))
			{
				dx = -0.01f;
			}
			if (pInput->GetPress(DIK_NUMPAD9))
			{
				dx = 0.01f;
			}
			if (pInput->GetPress(DIK_NUMPAD2))
			{
				dy = -0.01f;
			}
			if (pInput->GetPress(DIK_NUMPAD0))
			{
				dy = 0.01f;
			}
		}

		// マウス情報
		bool isMouseRight = false;
		CInputMouse* pMouse = CApplication::GetInstance()->GetMouse();
		if (pMouse != nullptr)
		{
			D3DXVECTOR3 dist = pMouse->GetMouseMoveDist();

			//if (pMouse->IsMouseButtonDrag(CInputMouse::MouseButtonType::Left))
			//{
			//	cx += dist.x * 0.0003f;
			//	cy += dist.y * 0.0003f;
			//	isMouseLeft = true;
			//}
			//else 
			if (pMouse->IsMouseButtonDrag(CInputMouse::MouseButtonType::Right))
			{
				dx += dist.x * 0.003f;
				dy += dist.y * 0.003f;
				isMouseRight = true;
			}
			else if (pMouse->IsMouseButtonDrag(CInputMouse::MouseButtonType::Center))
			{
				mx += dist.x * 0.5f;
				my -= dist.y * 0.5f;
			}

			if (dist.z > 0) {
				mz += 5.0f;
			}
			else if (dist.z < 0) {
				mz -= 5.0f;
			}
		}

		m_yaw += dx;
		m_pitch += dy;
		m_pitch = max(-D3DX_PI * 0.49f, min(D3DX_PI * 0.49f, m_pitch));	// 90度制限
		D3DXQuaternionRotationYawPitchRoll(&m_rotQuat, m_yaw, m_pitch, 0.0f);

		// カメラ視点移動
		m_Eye += m_Forward * mz;
		m_Eye += m_Right * mx;
		m_Eye += m_Up * my;
		m_LookAt += m_Right * mx;
		m_LookAt += m_Up * my;
	}
	else
#endif
	{
		m_yaw = 0.0f;
		m_pitch = 0.0f;
		m_rotSpeed = 0.0f;
		D3DXQuaternionIdentity(&m_rotQuat);
		if (m_targetObj != nullptr)
		{
			D3DXVECTOR3 buf = m_targetObj->GetPos();
			buf.x;
			buf.y += ADJUST_Y;
			buf.z -= m_Distance;
			m_LookAt = buf;

			m_move = (buf - m_Eye) * 0.1f;

			if (D3DXVec3LengthSq(&m_move) > 0.25f)
			{
				m_Eye += m_move;
			}
		}
	}


#if 0
	// ビュー行列初期化
	D3DXMatrixIdentity(&m_ViewMat);

	// ビュー行列作成
	D3DXMatrixLookAtLH(
		&m_ViewMat,
		&m_Eye,
		&m_LookAt,
		&m_Up);
#endif
	// 回転行列
	D3DXMATRIX rotMat;
	D3DXMatrixRotationQuaternion(&rotMat, &m_rotQuat);
	D3DXVECTOR3 dir = D3DXVECTOR3(0, 0, 1);
	D3DXVec3TransformCoord(&m_LookAt, &dir, &rotMat);
	// 視点・注視点の設定
	D3DXVec3Normalize(&m_LookAt, &m_LookAt);
	D3DXVec3Cross(&m_Right, &m_Up, &m_LookAt);
	D3DXVec3Normalize(&m_Right, &m_Right);
	D3DXMatrixIdentity(&m_ViewMat);
	D3DXVECTOR3 vec = (m_Eye + m_LookAt);

	// カメラを揺らす
	D3DXVECTOR3 shakeAdjust = D3DXVECTOR3(0, 0, 0);
	if (m_shakeFrame > 0)
	{
		m_shakeFrame--;
		shakeAdjust = D3DXVECTOR3((float)(rand() % m_shakeMagnitude), (float)(rand() % m_shakeMagnitude), (float)(rand() % m_shakeMagnitude));
	}

	// ビュー行列確定
	D3DXVECTOR3 eye = (m_Eye + shakeAdjust);
	D3DXVECTOR3 look = (vec + shakeAdjust);
	D3DXVECTOR3 up = (m_Up);
	D3DXMatrixLookAtLH(&m_ViewMat, &eye, &look, &up);

	// 前方方向	
	m_Forward = D3DXVECTOR3(rotMat._31, rotMat._32, rotMat._33);
	D3DXVec3Normalize(&m_Forward, &m_Forward);

	// ビュー行列の設定
	CRenderer* pRenderer = CApplication::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	pDevice->SetTransform(D3DTS_VIEW, &m_ViewMat);

	//m_Forward = D3DXVECTOR3(m_ViewMat._31, m_ViewMat._32, m_ViewMat._33);
	//D3DXVec3Normalize(&m_Forward, &m_Forward);
	//m_Right = D3DXVECTOR3(m_ViewMat._11, m_ViewMat._12, m_ViewMat._13);
	//D3DXVec3Normalize(&m_Right, &m_Right);
	//m_Up = D3DXVECTOR3(m_ViewMat._21, m_ViewMat._22, m_ViewMat._23);
	//D3DXVec3Normalize(&m_Up, &m_Up);
}

/// <summary>
/// 描画
/// </summary>
void CView::Draw()
{
	CRenderer* pRenderer = CApplication::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	
	// プロジェクション行列初期化
	D3DXMatrixIdentity(&m_ProjectionMat);

	switch (m_ViewSetting)
	{
	case CView::ViewSetting::Perspective:
		// 透視投影変換
		D3DXMatrixPerspectiveFovLH(
			&m_ProjectionMat,
			D3DXToRadian(45.0f),						// 視野角
			(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,	// アスペクト比
			10.0f,										// near
			1200.0f);									// far
		break;
	case CView::ViewSetting::Ortho:
		// 平行投影行変換
		D3DXMatrixOrthoLH(
			&m_ProjectionMat,
			(float)SCREEN_HEIGHT / 2.0f,
			(float)SCREEN_WIDTH / 3.0f / 2.0f,
			10.0f,
			1000.0f);
		break;
	default:
		assert(false);
		break;
	}

	// プロジェクション行列設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_ProjectionMat);
}

/// <summary>
/// デバッグ描画
/// </summary>
void CView::DebugDraw()
{
	//char text[256];
	//CRenderer* pRender = CApplication::GetInstance()->GetRenderer();

	//sprintf(&text[0], "Eye[x: %.2f , y: %.2f , z: %.2f ]", m_Eye.x, m_Eye.y, m_Eye.z);
	//pRender->DebugDrawText(text);
	//sprintf(&text[0], "LAt[x: %.2f , y: %.2f , z: %.2f ]", m_LookAt.x, m_LookAt.y, m_LookAt.z);
	//pRender->DebugDrawText(text);

}

/// <summary>
/// 生成
/// </summary>
/// <returns></returns>
CView* CView::Create()
{
	CView* pView;

	pView = DBG_NEW CView();

	pView->Init();

	return pView;
}

/// <summary>
/// 基準点取得
/// </summary>
/// <returns></returns>
const D3DXVECTOR3& CView::GetEye() const
{
	return m_Eye;
}

/// <summary>
/// 基準点設定
/// </summary>
/// <param name="eye"></param>
void CView::SetEye(const D3DXVECTOR3& eye)
{
	m_Eye = eye;
}

/// <summary>
/// 注視点取得
/// </summary>
/// <returns></returns>
const D3DXVECTOR3& CView::GetLookAt() const
{
	return m_LookAt;
}

/// <summary>
/// 注視点設定
/// </summary>
/// <param name="look"></param>
void CView::SetLookAt(const D3DXVECTOR3& look)
{
	m_LookAt = look;
}

/// <summary>
/// 上方向取得
/// </summary>
/// <returns></returns>
const D3DXVECTOR3& CView::GetUp() const
{
	return m_Up;
}

/// <summary>
/// 上方向設定
/// </summary>
/// <param name="up"></param>
void CView::SetUp(const D3DXVECTOR3& up)
{
	m_Up = up;
}

/// <summary>
/// 距離取得
/// </summary>
/// <returns></returns>
float CView::GetDistance()
{
	return m_Distance;
}

/// <summary>
/// 距離設定
/// </summary>
/// <param name="dist"></param>
void CView::SetDistance(float dist)
{
	m_Distance = dist;
}

/// <summary>
/// 前方取得
/// </summary>
/// <returns></returns>
const D3DXVECTOR3& CView::GetForward() const
{
	return m_Forward;
}

/// <summary>
/// 右方向取得
/// </summary>
/// <returns></returns>
const D3DXVECTOR3& CView::GetRight() const
{
	return m_Right;
}

float CView::GetYaw()
{
	return m_yaw;
}

float CView::GetPitch()
{
	return m_pitch;
}

/// <summary>
/// ターゲット取得
/// </summary>
/// <returns></returns>
CObject* CView::GetTargetObj()
{
	return m_targetObj;
}

/// <summary>
/// ターゲット設定
/// </summary>
/// <param name="pObj"></param>
void CView::SetTargetObj(CObject* pObj)
{
	m_targetObj = pObj;
}

/// <summary>
/// ビュー変換取得
/// </summary>
/// <returns></returns>
CView::ViewSetting CView::GetViewSetting()
{
	return m_ViewSetting;
}

/// <summary>
/// ビュー変換設定
/// </summary>
/// <param name="setting"></param>
void CView::SetViewSetting(ViewSetting setting)
{
	m_ViewSetting = setting;
}

void CView::ShakeCamera(int frame, int mag)
{
	m_shakeFrame = frame;
	m_shakeMagnitude = mag;
}
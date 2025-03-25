//*********************************************
//
// �|���S���`��(object2D.h)
// Author : Junichi Uchiyama
//
//*********************************************

#include "object2D.h"
#include "renderer.h"
#include "application.h"
#include "input.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
CObject2D::CObject2D(CObject::Priority priority) : CObject(priority)
{
	m_pVtxBuf = nullptr;
	m_pTexture = nullptr;
	m_size = D3DXVECTOR2(100, 100);
	SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	m_uv.leftU = m_uv.topV = 0.0f;
	m_uv.rightU = m_uv.bottomV = 1.0f;

	m_posType = POSTYPE::Center;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CObject2D::~CObject2D()
{

}

// �|���S��������
HRESULT CObject2D::Init()
{
	CRenderer* pRenderer = CApplication::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// ���_�o�b�t�@
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuf,
		NULL);

	//// �e�N�X�`��
	//if (FAILED(D3DXCreateTextureFromFile(pDevice,
	//	"data/sample/player000.png",
	//	&m_pTexture)))
	//{
	//	assert(false);
	//}

	// ���_���X�V
	UpdateVertex();

	return S_OK;
}

/// <summary>
/// �|���S���I��
/// </summary>
void CObject2D::Uninit()
{
	// ���_�o�b�t�@
	if (m_pVtxBuf != nullptr)
	{
		m_pVtxBuf->Release();
		m_pVtxBuf = nullptr;
	}

	//if (m_pTexture != nullptr)
	//{
	//	m_pTexture->Release();
	//	m_pTexture = nullptr;
	//}

	// ���g��j��
	Release();
}

/// <summary>
/// �|���S���X�V
/// </summary>
void CObject2D::Update()
{
	if (m_pVtxBuf != nullptr)
	{
		// ���_���X�V
		UpdateVertex();
	}
}

/// <summary>
/// �|���S���`��
/// </summary>
void CObject2D::Draw()
{
	if (m_pVtxBuf != nullptr)
	{
		CRenderer* pRenderer = CApplication::GetInstance()->GetRenderer();
		LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

		// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, m_pVtxBuf, 0, sizeof(VERTEX_2D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, m_pTexture);

		// �`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	}
}

/// <summary>
/// �e�N�X�`�����f
/// </summary>
/// <param name="pTexture"></param>
void CObject2D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

/// <summary>
/// ���_���X�V
/// </summary>
void CObject2D::UpdateVertex()
{
	D3DXVECTOR3 scale = GetScale();
	D3DXVECTOR3 pos = GetPos();

	// �|���S�����_
	VERTEX_2D* pVtx;
	m_pVtxBuf->Lock(0, 0, (void**)&pVtx, 0);

	// ���W
	float w = 1280.0f;
	float h = 720.0f;
	switch (m_posType)
	{
	case CObject2D::POSTYPE::Center:
		w = m_size.x / 2.0f * scale.x;
		h = m_size.y / 2.0f * scale.y;
		pVtx[0].pos = D3DXVECTOR3(pos.x - w, pos.y - h, 0);
		pVtx[1].pos = D3DXVECTOR3(pos.x + w, pos.y - h, 0);
		pVtx[2].pos = D3DXVECTOR3(pos.x - w, pos.y + h, 0);
		pVtx[3].pos = D3DXVECTOR3(pos.x + w, pos.y + h, 0);
		break;
	case CObject2D::POSTYPE::Under:
		w = m_size.x / 2.0f * scale.x;
		h = m_size.y * scale.y;
		pVtx[0].pos = D3DXVECTOR3(pos.x - w, pos.y - h, 0);
		pVtx[1].pos = D3DXVECTOR3(pos.x + w, pos.y - h, 0);
		pVtx[2].pos = D3DXVECTOR3(pos.x - w, pos.y, 0);
		pVtx[3].pos = D3DXVECTOR3(pos.x + w, pos.y, 0);
		break;
	case CObject2D::POSTYPE::LeftTop:
		w = m_size.x * scale.x;
		h = m_size.y * scale.y;
		pVtx[0].pos = D3DXVECTOR3(pos.x, pos.y, 0);
		pVtx[1].pos = D3DXVECTOR3(pos.x + w, pos.y, 0);
		pVtx[2].pos = D3DXVECTOR3(pos.x, pos.y + h, 0);
		pVtx[3].pos = D3DXVECTOR3(pos.x + w, pos.y + h, 0);
		break;
	default:
		assert(false);
		break;
	}

	// rhw
	pVtx[0].rhw = pVtx[1].rhw = pVtx[2].rhw = pVtx[3].rhw = 1.0f;

	// ø������W
	pVtx[0].tex = D3DXVECTOR2(m_uv.leftU, m_uv.topV);
	pVtx[1].tex = D3DXVECTOR2(m_uv.rightU, m_uv.topV);
	pVtx[2].tex = D3DXVECTOR2(m_uv.leftU, m_uv.bottomV);
	pVtx[3].tex = D3DXVECTOR2(m_uv.rightU, m_uv.bottomV);

	// �J���[
	pVtx[0].col = pVtx[1].col = pVtx[2].col = pVtx[3].col = GetColor();

	m_pVtxBuf->Unlock();
}

/// <summary>
/// �����i�`�揇���l���������ꍇ�͐ݒ肷��j
/// </summary>
/// <returns></returns>
CObject2D* CObject2D::Create(CObject::Priority priority)
{
	CObject2D* pObj;

	pObj = DBG_NEW CObject2D(priority);
	if (pObj != nullptr)
	{
		pObj->Init();
	}

	return pObj;
}

/// <summary>
/// �T�C�Y�擾
/// </summary>
/// <returns></returns>
const D3DXVECTOR2& CObject2D::GetSize() const
{
	return m_size;
}

/// <summary>
/// �T�C�Y�ݒ�
/// </summary>
/// <param name="pos"></param>
void CObject2D::SetSize(const D3DXVECTOR2& size)
{
	m_size = size;
}

/// <summary>
/// UV���W�擾
/// </summary>
/// <returns>left:startU, top:startV, bottom:endV, right:endU</returns>
const TEXTURE_UV& CObject2D::GetUV() const
{
	return m_uv;
}

/// <summary>
/// UV���W�ݒ�
/// </summary>
/// <param name="uv">left:startU, top:startV, bottom:endV, right:endU</param>
void CObject2D::SetUV(const TEXTURE_UV& uv)
{
	m_uv = uv;
}

/// <summary>
/// ���_�ʒu�ݒ���@�̎擾
/// </summary>
/// <returns></returns>
const CObject2D::POSTYPE& CObject2D::GetPosType() const
{
	return m_posType;
}

/// <summary>
/// UV���W�ݒ�
/// </summary>
/// <param name="uv">left:startU, top:startV, bottom:endV, right:endU</param>
void CObject2D::SetPosType(const CObject2D::POSTYPE& type)
{
	m_posType = type;
}


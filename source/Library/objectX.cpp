//*********************************************
//
// �I�u�W�F�N�gX(objectX.cpp)
// Author : Junichi Uchiyama
//
//*********************************************

#include "objectX.h"
#include "application.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="priority"></param>
CObjectX::CObjectX(Priority priority): CObject3D(priority)
{
	m_pMesh = nullptr;
	m_pMaterialBuf = nullptr;
	m_MaterialNum = 0;

	m_vtxLocalMin = D3DXVECTOR3(0, 0, 0);
	m_vtxLocalMax = D3DXVECTOR3(0, 0, 0);

	m_pTexture = nullptr;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CObjectX::~CObjectX()
{

}

/// <summary>
/// ������
/// </summary>
/// <returns></returns>
HRESULT CObjectX::Init()
{
	// ���_���̎擾
	int nNumVtx = m_pMesh->GetNumVertices();
	// ���_�t�H�[�}�b�g�̃T�C�Y���擾
	DWORD sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());
	// ���_�o�b�t�@�̃��b�N
	BYTE* pVtxBuff;
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	// ���_���W�̑��
	m_vtxLocalMin = D3DXVECTOR3(0, 0, 0);
	m_vtxLocalMax = D3DXVECTOR3(0, 0, 0);
	for (int i = 0; i < nNumVtx; i++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		// ���_���W���r���ă��f���̍ő�ŏ��l���擾

		if (vtx.x > m_vtxLocalMax.x) {
			m_vtxLocalMax.x = vtx.x;
		}
		if (vtx.y > m_vtxLocalMax.y) {
			m_vtxLocalMax.y = vtx.y;
		}
		if (vtx.z > m_vtxLocalMax.z) {
			m_vtxLocalMax.z = vtx.z;
		}

		if (vtx.x < m_vtxLocalMin.x) {
			m_vtxLocalMin.x = vtx.x;
		}
		if (vtx.y < m_vtxLocalMin.y) {
			m_vtxLocalMin.y = vtx.y;
		}
		if (vtx.z < m_vtxLocalMin.z) {
			m_vtxLocalMin.z = vtx.z;
		}

		// ���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
		pVtxBuff += sizeFVF;
	}

	// ���_�o�b�t�@�̃A�����b�N
	m_pMesh->UnlockVertexBuffer();

	return S_OK;
}

/// <summary>
/// ���
/// </summary>
void CObjectX::Uninit()
{
	if (m_pMesh != nullptr)
	{
		m_pMesh->Release();
		m_pMesh = nullptr;
	}

	if (m_pMaterialBuf != nullptr)
	{
		m_pMaterialBuf->Release();
		m_pMesh = nullptr;
	}

	CObject3D::Uninit();
}

/// <summary>
/// �X�V
/// </summary>
void CObjectX::Update()
{
	CObject3D::Update();
}

/// <summary>
/// �`��
/// </summary>
void CObjectX::Draw()
{
	CRenderer* pRenderer = CApplication::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DMATERIAL9 matBuf;			// ���݂̃}�e���A���ۑ��p�o�b�t�@
	D3DXMATERIAL* pMat;				// �}�e���A���f�[�^

	// ���[���h�s��̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &GetWorldMat());

	// ���݂̃}�e���A����ێ�
	pDevice->GetMaterial(&matBuf);
	D3DXCOLOR col = GetColor();

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pMaterialBuf->GetBufferPointer();
	for (int count = 0; count < (int)m_MaterialNum; count++)
	{
		// �}�e���A���̐ݒ�
		pMat[count].MatD3D.Ambient = pMat[count].MatD3D.Diffuse;
		pMat[count].MatD3D.Emissive = pMat[count].MatD3D.Diffuse;
		pDevice->SetMaterial(&pMat[count].MatD3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, m_pTexture);

		// ���f���p�[�c�̕`��
		m_pMesh->DrawSubset(count);
	}

	// �ێ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matBuf);
}

/// <summary>
/// X�t�@�C���ǂݍ���
/// </summary>
/// <param name="filename"></param>
/// <returns></returns>
HRESULT CObjectX::LoadXFile(const char* filename)
{
	CRenderer* pRenderer = CApplication::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// X�t�@�C���̓ǂݍ���
	if (FAILED(D3DXLoadMeshFromX(filename,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pMaterialBuf,
		NULL,
		&m_MaterialNum,
		&m_pMesh)))
	{
		return E_FAIL;
	}

	// �e�N�X�`���Ǎ�
	D3DXMATERIAL* pMat = (D3DXMATERIAL*)m_pMaterialBuf->GetBufferPointer();
	for (int i = 0; i < (int)m_MaterialNum; i++)
	{
		if (pMat[i].pTextureFilename != NULL)
		{
			int size = (int)strlen(pMat[i].pTextureFilename);
			if (size > 0) {
				char path[256];
				int filename_len = (int)strlen(filename);
				memcpy(path, filename, sizeof(char) * filename_len);
				path[filename_len] = '\0';
				int index = 0;
				for (index = filename_len; index >= 0; index--)
				{
					if (path[index] == '/')
					{
						path[index + 1] = '\0';
						break;
					}
				}
				strcat(path, pMat[i].pTextureFilename);

				// �e�N�X�`���쐬
				//if (FAILED(D3DXCreateTextureFromFileEx(
				//	pDevice,			// pDevice   :IDirect3DDevice
				//	path,				// pSrcFile  :�摜�t�@�C���ւ̐�΃p�X�y�ё��̃p�X(bmp, dds, dib, jpg, png, tga)
				//	D3DX_DEFAULT,		// Width     :�쐬����e�N�X�`���T�C�Y�iD3DX_DEFAULT���w�肷���256�s�N�Z���j
				//	D3DX_DEFAULT,		// Height    :�쐬����e�N�X�`���T�C�Y�iD3DX_DEFAULT���w�肷���256�s�N�Z���j
				//	0,					// MipLevels :�~�b�v�}�b�v���x��
				//	0,					// Usage     :�e�N�X�`���̐�����m�ۃ������ꏊ�̎w��
				//	D3DFMT_UNKNOWN,		// Format    :�e�N�X�`���̃s�N�Z���t�H�[�}�b�g���w��
				//	D3DPOOL_DEFAULT,	// Pool      :�e�N�X�`�����i�[���郁�����̈ʒu�ƊǗ��t���O
				//	D3DX_FILTER_POINT,	// Filter    :�C���[�W�̃t�B���^�����O���@�w��
				//	D3DX_DEFAULT,		// MipFilter :�~�b�v�}�b�v�ɑ΂��Ẵt�B���^�����O
				//	0,					// ColorKey  :���S�ɓ����ɂ���F���w��\
				//	nullptr,			// pSrcInfo  :���̉摜�̏����i�[����D3DXIMAGE_INFO�\���̃|�C���^�󂯓n��
				//	nullptr,			// pPalette  :256�F�t�H�[�}�b�g�̏ꍇ�̂݉摜�Ɏg���Ă���p���b�g�ւ̃|�C���^�󂯓n��	
				//	&m_pTexture)))		// ppTexture :���������e�N�X�`���I�u�W�F�N�g�̃|�C���^
				//{
				//	return E_FAIL;
				//}
				auto pTex = CApplication::GetInstance()->GetTexture();
				int tempID = pTex->LoadTexture(path);
				m_pTexture = pTex->GetTexture(tempID);
			}
		}
	}

	return S_OK;
}

/// <summary>
/// �J���[�𔽉f����
/// </summary>
/// <param name="color"></param>
void CObjectX::SetColor(const D3DXCOLOR& col)
{
	CObject::SetColor(col);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	D3DXMATERIAL* pMat = (D3DXMATERIAL*)m_pMaterialBuf->GetBufferPointer();
	pMat[0].MatD3D.Diffuse = D3DXCOLOR(GetColor());
	pMat[0].MatD3D.Ambient = pMat[0].MatD3D.Diffuse;
	pMat[0].MatD3D.Emissive = pMat[0].MatD3D.Diffuse;
	pMat[0].MatD3D.Power = 0.0f;
	pMat[0].MatD3D.Specular = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

/// <summary>
/// �e�N�X�`���̔��f
/// </summary>
/// <param name="pTex"></param>
void CObjectX::BindTexture(LPDIRECT3DTEXTURE9 pTex)
{
	m_pTexture = pTex;
}

/// <summary>
/// ����
/// </summary>
/// <param name="pos"></param>
/// <param name="filename"></param>
/// <returns></returns>
CObjectX* CObjectX::Create(const D3DXVECTOR3& pos, const char* filename)
{
	CObjectX* pObjX;

	pObjX = DBG_NEW CObjectX();

	pObjX->LoadXFile(filename);
	pObjX->SetPos(pos);
	pObjX->Init();

	return pObjX;
}
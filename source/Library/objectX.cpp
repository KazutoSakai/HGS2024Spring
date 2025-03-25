//*********************************************
//
// オブジェクトX(objectX.cpp)
// Author : Junichi Uchiyama
//
//*********************************************

#include "objectX.h"
#include "application.h"

/// <summary>
/// コンストラクタ
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
/// デストラクタ
/// </summary>
CObjectX::~CObjectX()
{

}

/// <summary>
/// 初期化
/// </summary>
/// <returns></returns>
HRESULT CObjectX::Init()
{
	// 頂点数の取得
	int nNumVtx = m_pMesh->GetNumVertices();
	// 頂点フォーマットのサイズを取得
	DWORD sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());
	// 頂点バッファのロック
	BYTE* pVtxBuff;
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	// 頂点座標の代入
	m_vtxLocalMin = D3DXVECTOR3(0, 0, 0);
	m_vtxLocalMax = D3DXVECTOR3(0, 0, 0);
	for (int i = 0; i < nNumVtx; i++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		// 頂点座標を比較してモデルの最大最小値を取得

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

		// 頂点フォーマットのサイズ分ポインタを進める
		pVtxBuff += sizeFVF;
	}

	// 頂点バッファのアンロック
	m_pMesh->UnlockVertexBuffer();

	return S_OK;
}

/// <summary>
/// 解放
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
/// 更新
/// </summary>
void CObjectX::Update()
{
	CObject3D::Update();
}

/// <summary>
/// 描画
/// </summary>
void CObjectX::Draw()
{
	CRenderer* pRenderer = CApplication::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DMATERIAL9 matBuf;			// 現在のマテリアル保存用バッファ
	D3DXMATERIAL* pMat;				// マテリアルデータ

	// ワールド行列の設定
	pDevice->SetTransform(D3DTS_WORLD, &GetWorldMat());

	// 現在のマテリアルを保持
	pDevice->GetMaterial(&matBuf);
	D3DXCOLOR col = GetColor();

	// マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pMaterialBuf->GetBufferPointer();
	for (int count = 0; count < (int)m_MaterialNum; count++)
	{
		// マテリアルの設定
		pMat[count].MatD3D.Ambient = pMat[count].MatD3D.Diffuse;
		pMat[count].MatD3D.Emissive = pMat[count].MatD3D.Diffuse;
		pDevice->SetMaterial(&pMat[count].MatD3D);

		// テクスチャの設定
		pDevice->SetTexture(0, m_pTexture);

		// モデルパーツの描画
		m_pMesh->DrawSubset(count);
	}

	// 保持していたマテリアルを戻す
	pDevice->SetMaterial(&matBuf);
}

/// <summary>
/// Xファイル読み込み
/// </summary>
/// <param name="filename"></param>
/// <returns></returns>
HRESULT CObjectX::LoadXFile(const char* filename)
{
	CRenderer* pRenderer = CApplication::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// Xファイルの読み込み
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

	// テクスチャ読込
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

				// テクスチャ作成
				//if (FAILED(D3DXCreateTextureFromFileEx(
				//	pDevice,			// pDevice   :IDirect3DDevice
				//	path,				// pSrcFile  :画像ファイルへの絶対パス及び総体パス(bmp, dds, dib, jpg, png, tga)
				//	D3DX_DEFAULT,		// Width     :作成するテクスチャサイズ（D3DX_DEFAULTを指定すると256ピクセル）
				//	D3DX_DEFAULT,		// Height    :作成するテクスチャサイズ（D3DX_DEFAULTを指定すると256ピクセル）
				//	0,					// MipLevels :ミップマップレベル
				//	0,					// Usage     :テクスチャの性質や確保メモリ場所の指定
				//	D3DFMT_UNKNOWN,		// Format    :テクスチャのピクセルフォーマットを指定
				//	D3DPOOL_DEFAULT,	// Pool      :テクスチャを格納するメモリの位置と管理フラグ
				//	D3DX_FILTER_POINT,	// Filter    :イメージのフィルタリング方法指定
				//	D3DX_DEFAULT,		// MipFilter :ミップマップに対してのフィルタリング
				//	0,					// ColorKey  :完全に透明にする色を指定可能
				//	nullptr,			// pSrcInfo  :元の画像の情報を格納するD3DXIMAGE_INFO構造体ポインタ受け渡し
				//	nullptr,			// pPalette  :256色フォーマットの場合のみ画像に使われているパレットへのポインタ受け渡し	
				//	&m_pTexture)))		// ppTexture :生成したテクスチャオブジェクトのポインタ
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
/// カラーを反映する
/// </summary>
/// <param name="color"></param>
void CObjectX::SetColor(const D3DXCOLOR& col)
{
	CObject::SetColor(col);

	// マテリアルデータへのポインタを取得
	D3DXMATERIAL* pMat = (D3DXMATERIAL*)m_pMaterialBuf->GetBufferPointer();
	pMat[0].MatD3D.Diffuse = D3DXCOLOR(GetColor());
	pMat[0].MatD3D.Ambient = pMat[0].MatD3D.Diffuse;
	pMat[0].MatD3D.Emissive = pMat[0].MatD3D.Diffuse;
	pMat[0].MatD3D.Power = 0.0f;
	pMat[0].MatD3D.Specular = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

/// <summary>
/// テクスチャの反映
/// </summary>
/// <param name="pTex"></param>
void CObjectX::BindTexture(LPDIRECT3DTEXTURE9 pTex)
{
	m_pTexture = pTex;
}

/// <summary>
/// 生成
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
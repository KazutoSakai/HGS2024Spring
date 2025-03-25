//*********************************************
//
// テクスチャ(texture.cpp)
// Author : Junichi Uchiyama
//
//*********************************************

#include "texture.h"
#include "application.h"

/// <summary>
/// コンストラクタ
/// </summary>
CTexture::CTexture()
{
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		m_pTextures[i] = nullptr;
		ZeroMemory(&m_apTexName[i][0], sizeof(char) * 256);
	}
}

/// <summary>
/// デストラクタ
/// </summary>
CTexture::~CTexture()
{

}

/// <summary>
/// 個別破棄
/// </summary>
/// <param name="id"></param>
void CTexture::ReleaseTexture(int id)
{
	if (id < TEXTURE_MAX)
	{
		if (m_pTextures[id] != nullptr)
		{
			m_pTextures[id]->Release();
			m_pTextures[id] = nullptr;
		}
	}
}

/// <summary>
/// 全破棄
/// </summary>
void CTexture::ReleaseAll()
{
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		if (m_pTextures[i] != nullptr)
		{
			ReleaseTexture(i);
		}
	}
}

/// <summary>
/// テクスチャ
/// </summary>
/// <param name="filename"></param>
/// <returns></returns>
int CTexture::LoadTexture(const char* filename)
{
	CRenderer* pRenderer = CApplication::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	int id = -1;

	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		if (m_pTextures[i] == nullptr)
		{
			if (FAILED(D3DXCreateTextureFromFile(pDevice,
				filename,
				&m_pTextures[i])))
			{
				assert(false);
			}
			strcpy(&m_apTexName[i][0], filename);

			id = i;
			break;
		}
		else
		{
			if (strcmp(&m_apTexName[i][0], filename) == 0)
			{
				id = i;
				break;
			}
		}
	}

	return id;
}

/// <summary>
/// テクスチャ情報
/// </summary>
/// <param name="id"></param>
/// <returns></returns>
LPDIRECT3DTEXTURE9 CTexture::GetTexture(int id)
{
	return m_pTextures[id];
}
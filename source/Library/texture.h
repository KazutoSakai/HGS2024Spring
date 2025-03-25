//*********************************************
//
// テクスチャ管理クラス(texture.h)
// Author : Junichi Uchiyama
//
//*********************************************

#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "main.h"

class CTexture
{
private:
	//---------------------
	// 定数
	static const int TEXTURE_MAX = 256;		// テクスチャ最大数
	static const int FILEPATH_MAX = 256;	// 保存するパスの最大文字数
	
public:
	//---------------------
	// public Method
	CTexture();			// コンストラクタ
	~CTexture();		// デストラクタ

	void ReleaseTexture(int id);	// 解放
	void ReleaseAll();				// 全解放
	int LoadTexture(const char* filename);		// テクスチャ読込
	LPDIRECT3DTEXTURE9 GetTexture(int id);		// テクスチャ取得
	
private:
	//---------------------
	// private Member
	LPDIRECT3DTEXTURE9 m_pTextures[TEXTURE_MAX];		// テクスチャデータ
	char m_apTexName[TEXTURE_MAX][FILEPATH_MAX];		// 登録済み判別用
};

#endif
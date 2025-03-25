//*********************************************
//
// �e�N�X�`���Ǘ��N���X(texture.h)
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
	// �萔
	static const int TEXTURE_MAX = 256;		// �e�N�X�`���ő吔
	static const int FILEPATH_MAX = 256;	// �ۑ�����p�X�̍ő啶����
	
public:
	//---------------------
	// public Method
	CTexture();			// �R���X�g���N�^
	~CTexture();		// �f�X�g���N�^

	void ReleaseTexture(int id);	// ���
	void ReleaseAll();				// �S���
	int LoadTexture(const char* filename);		// �e�N�X�`���Ǎ�
	LPDIRECT3DTEXTURE9 GetTexture(int id);		// �e�N�X�`���擾
	
private:
	//---------------------
	// private Member
	LPDIRECT3DTEXTURE9 m_pTextures[TEXTURE_MAX];		// �e�N�X�`���f�[�^
	char m_apTexName[TEXTURE_MAX][FILEPATH_MAX];		// �o�^�ςݔ��ʗp
};

#endif
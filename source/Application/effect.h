//*********************************************
//
// �G�t�F�N�g(effect.h)
// Author : Junichi Uchiyama
//
//*********************************************

#include "object2D.h"

class CEffect : public CObject2D
{
public:
	CEffect(Priority priority = Priority::Effect_Low);	// �R���X�g���N�^
	~CEffect() override;								// �f�X�g���N�^

	HRESULT Init() override;							// ������
	void Uninit() override;								// ���
	void Update() override;								// �X�V
	void Draw() override;								// �`��

	static HRESULT Load();								// �Ǎ�
	static void UnLoad();								// �j��
	static CEffect* Create(const D3DXVECTOR3& pos, const D3DXCOLOR& col, int life);		// ����

	int GetLife();										// �����擾
	void SetLife(int life);								// �����ݒ�

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;				// �e�N�X�`��

	int m_life;											// ����
};
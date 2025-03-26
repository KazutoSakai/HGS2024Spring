//*********************************************
//
// �����\��(number.h)
// Author : Junichi Uchiyama
//
//*********************************************

#ifndef _NUMBER_H_
#define _NUMBER_H_

#include "object2D.h"

/// <summary>
/// �����Ǘ�
/// </summary>
class CNumber : public CObject2D
{
public:
	CNumber(Priority priority = Priority::UI);		// �R���X�g���N�^
	~CNumber();		// �f�X�g���N�^

	HRESULT Init() override;	// ������
	void Uninit() override;		// ���
	void Update() override;		// �X�V
	void Draw() override;		// �`��

	static CNumber* Create(const D3DXVECTOR3& pos);		// ����

	void SetNumber(int num);		// �����ݒ�

private:

};

#endif
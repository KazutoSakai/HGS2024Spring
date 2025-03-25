//*********************************************
//
// 3D�r���[����(view.h)
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

	// �`����@�̐ݒ�
	enum class ViewSetting
	{
		Perspective=0,		// �����ˉe�ϊ�
		Ortho,				// ���s���e�ϊ�

		Max,
	};

	//---------------------
	// public Method
	CView(Priority priority = Priority::View);		// �R���X�g���N�^
	~CView() override;								// �f�X�g���N�^

	HRESULT Init() override;						// ������
	void Uninit() override;							// ���
	void Update() override;							// �X�V
	void Draw() override;							// �`��
	void DebugDraw() override;						// �f�o�b�O�`��

	void ShakeCamera(int frame, int mag);			// �J�����h������s����

	//---------------------
	// static Method
	static CView* Create();							// ����
	
	//---------------------
	// Getter Setter
	const D3DXVECTOR3& GetEye() const;				// ��_�擾
	void SetEye(const D3DXVECTOR3& eye);			// ��_�ݒ�

	const D3DXVECTOR3& GetLookAt() const;			// ��_�擾
	void SetLookAt(const D3DXVECTOR3& look);		// ��_�ݒ�

	const D3DXVECTOR3& GetUp() const;				// ��_�擾
	void SetUp(const D3DXVECTOR3& up);				// ��_�ݒ�

	float GetDistance();							// �����擾
	void SetDistance(float dist);					// �����ݒ�

	const D3DXVECTOR3& GetForward() const;			// �O���擾
	const D3DXVECTOR3& GetRight() const;			// �E�����擾

	float GetYaw();									// ���[�擾
	float GetPitch();								// ���[���擾

	CObject* GetTargetObj();						// �����_�Ώێ擾
	void SetTargetObj(CObject* pObj);				// �����_�Ώېݒ�

	ViewSetting GetViewSetting();					// �r���[�ϊ��擾
	void SetViewSetting(ViewSetting setting);		// �r���[�ϊ��ݒ�

private:
	//---------------------
	// static Member
	static const int MAX_PARAM = 100;
	static constexpr float ADJUST_Y = 30.0f;

	//---------------------
	// private Member
	D3DXVECTOR3 m_Eye;								// ��_
	D3DXVECTOR3 m_LookAt;							// �����_
	D3DXVECTOR3 m_Up;								// �����

	D3DXMATRIX m_ProjectionMat;						// �ˉe�ϊ��s��
	D3DXMATRIX m_ViewMat;							// �r���[�s��

	D3DXVECTOR3 m_Forward;							// �J�����̑O������
	D3DXVECTOR3 m_Right;							// �J������
	float m_Distance;

	ViewSetting m_ViewSetting;

	// �N�H�[�^�j�I��
	D3DXQUATERNION m_rotQuat;
	float m_yaw;
	float m_pitch;
	float m_rotSpeed;

	// ���b�N�I��
	CObject* m_targetObj;
	D3DXVECTOR3 m_move;

	int m_shakeFrame;
	int m_shakeMagnitude;
};

#endif
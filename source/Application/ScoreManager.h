#ifndef _SCOREMANAGER_H_
#define _SCOREMANAGER_H_

#include "number.h"

class CScoreManager
{
public:

	//---------------------
	// Singleton
	static CScoreManager* GetInstance()
	{
		static CScoreManager instance;
		return &instance;
	}
	CScoreManager(const CScoreManager&) = delete;
	CScoreManager& operator=(const CScoreManager&) = delete;
	CScoreManager(CScoreManager&&) = delete;
	CScoreManager& operator=(CScoreManager&&) = delete;

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
	void AddScore(int score);
	void SetScore(int score);
	void SetDestScore(int dest) { m_destScore = dest; }

	void ResultScore();
	void LatestScore();

	int GetScore() { return m_score; }
	int GetDestScore() { return m_destScore; }

private:
	static const int SCORE_NUM = 8;

	//---------------------
	// default
	CScoreManager();					// �R���X�g���N�^
	~CScoreManager();					// �f�X�g���N�^

	CNumber* m_pNumberList[SCORE_NUM];
	int m_score;			// ���݂̃X�R�A
	int m_destScore;		// �ڕW�l�̃X�R�A

};

#endif
//=============================================================================
//
// Game�V�[��UI�Ǘ����� [GameSceneUIMaager.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _GAMESCENEUIMANAGER_H_
#define _GAMESCENEUIMANAGER_H_

/**************************************
�O���錾
***************************************/
class Object;
class Guage;
class Combo;
class Cursor;
class Line;
class Score;
class Star;
class Trail;
class TelopBG;
class BattleStartTelop;
class StageClearTelop;

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
class GameSceneUIManager
{
public:
	GameSceneUIManager();
	~GameSceneUIManager();

	Guage*guage;
	Combo*combo;
	Cursor*cursor;
	Line*line;
	Score*score;
	Star*star;
	Trail*trail;
	TelopBG*telopBG;
	BattleStartTelop*battleStartTelop;
	StageClearTelop*stageClearTelop;

	void Init(void);
	void Uninit(void);
	void Update(HWND hwnd);
	void Draw(void);

	//=============================================================================
	// �R���{�̉��Z�i�����Ŏ󂯎�����l���R���{�ɉ��Z����j
	//=============================================================================
	void AddCombo(int value)
	{
		combo->combo += value;

		if (value > 0)
		{
			combo->volumeUpEffectUsed = true;
		}
	}
	//=============================================================================
	// �R���{�̃Z�b�g
	//=============================================================================
	void SetCombo(int num)
	{
		num  = combo->combo;
	}

	//=============================================================================
	// �R���{�̃��Z�b�g
	//=============================================================================
	void ReSetCombo(void)
	{
		combo->combo = 0;
	}

	//=============================================================================
	// �X�R�A�̉��Z�i�����Ŏ󂯎�����l���X�R�A�ɉ��Z����j
	//=============================================================================
	void AddScore(int value)
	{
		score += value;

		// �X�R�A�����Z���ꂽ��s������
		if (value > 0)
		{
			// �G�t�F�N�g�L����
			score->volumeUpEffectUsed = true;
		}
	}

	//=============================================================================
	// �X�R�A�̃Z�b�g
	//=============================================================================
	void SetScore(int num)
	{
		num = score->score;
	}

	//=============================================================================
	// HP�̉��Z�i�����Ŏ󂯎�����l��HO�ɉ��Z����j
	//=============================================================================
	void AddHp(float value)
	{
		guage->trueGuagePercentage += (value /= guage->maxHp);
	}

	//=============================================================================
	// �X�e�[�W�N���A�e���b�v�Z�b�g����
	//=============================================================================
	void SetStageClearTelop(void)
	{
		stageClearTelop->isStageClearTelopActivated = true;
	}

	//=============================================================================
	// �o�g���X�^�[�g�e���b�v�Z�b�g����
	//=============================================================================
	void SetBattleStartTelop(void)
	{
		battleStartTelop->isBattleStartTelopActivated = true;
	}

	//=============================================================================
	// �X�^�[���W�Q�b�g����
	//=============================================================================
	D3DXVECTOR3* GetStarPosition(void)
	{
		return star->GetStarPosition();
	}

	//=============================================================================
	// �X�^�[���W�Z�b�g����
	//=============================================================================
	void SetStarPosition(D3DXVECTOR3* pos)
	{
		pos = star->GetStarPosition();
	}


private:
	bool IsStarCursorOvered();
	void UpdateCursorColor();
};

#endif


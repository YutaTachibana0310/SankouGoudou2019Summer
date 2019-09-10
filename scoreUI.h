//=============================================================================
//
// �X�R�A���� [score.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	INTERVAL_NUMBER	(120.0f)		// �X�R�A�����̕\���Ԋu
#define	INTERVAL_RANKING_NUMBER	(45.0f)	// �X�R�A�����̕\���Ԋu�i�����L���O�p�j
#define	INTERVAL_NUMBER_TEXTURE	(0.1f)	// �e�N�X�`���e�N�X�`�����̃X�R�A�����̕\���Ԋu
#define	PLACE_MAX		(6)				// �X�R�A�̌���
#define BASE_NUMBER		(10)			// �i��
#define VOLUME_ZOOM		(30.0f)

/**************************************
�O���錾
***************************************/
class CounterObject;
class Object;
class Viewer3D;

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
class Score
{
public:
	Score();
	~Score();

	int	score;		// �X�R�A
	int	score_max;

	float radian;
	bool volumeUpEffectUsed;

	void Update(void);
	void Draw(void);

private:
	Object * bg;
	CounterObject * counter;
	Viewer3D * viewer;

	void VolumeUpEffect(void);
};

#endif

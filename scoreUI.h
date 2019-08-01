//=============================================================================
//
// �X�R�A���� [score.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	ADRESS_TEXTURE_SCORE		"data/TEXTURE/UI/number.png"	// �ǂݍ��ރe�N�X�`���t�@�C����

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	INTERVAL_NUMBER	(40.0f)				// �X�R�A�����̕\���Ԋu
#define	INTERVAL_RANKING_NUMBER	(50.0f)		// �X�R�A�����̕\���Ԋu�i�����L���O�p�j
#define	INTERVAL_NUMBER_TEXTURE	(0.097f)	// �e�N�X�`���e�N�X�`�����̃X�R�A�����̕\���Ԋu
#define	PLACE_MAX		(4)					// �X�R�A�̌���
#define BASE_NUMBER		(10)				// �i��
#define VOLUME_ZOOM		(30.0f)
#define SIZE_SCORE		(D3DXVECTOR3(20.0f,30.0f,0.0f))
#define POSITION_SCORE	(D3DXVECTOR3(SCREEN_WIDTH / 10 * 8.8f, SCREEN_HEIGHT / 10 * 8, 0.0f))

#include "GameSceneUIManager.h"
#include "UIdrawer.h"

class Object;

/**************************************
�O���錾
***************************************/
class GameSceneUI;

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
class Score :public GameSceneUI
{
public:
	Object*object;
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void AddScore(int value);
	int SetScore();

private:
	void VolumeUpEffect(void);
};

#endif

//=============================================================================
//
// �X�^�[��ʏ��� [star.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _STAR_H_
#define _STAR_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	ADRESS_TEXTURE_STAR	("data/TEXTURE/UI/star.png")	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	STAR_MAX			(5)

#define COLLIDERSIZE_STAR			(D3DXVECTOR3(250.0f,250.0f,0.0f))

// ���W��`
#define POSITION_STAR_TOP			(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 5, 0.0f))
#define POSITION_STAR_MIDDLE_LEFT	(D3DXVECTOR3(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 5*2, 0.0f))
#define POSITION_STAR_LOWER_LEFT	(D3DXVECTOR3(SCREEN_WIDTH / 3*1.2, SCREEN_HEIGHT / 5*4, 0.0f))
#define POSITION_STAR_LOWER_RIGHT	(D3DXVECTOR3(SCREEN_WIDTH / 3*1.8, SCREEN_HEIGHT / 5*4, 0.0f))
#define POSITION_STAR_MIDDLE_RIGHT	(D3DXVECTOR3(SCREEN_WIDTH / 3*2, SCREEN_HEIGHT / 5*2, 0.0f))
#define POSITION_STAR_CENTER		(D3DXVECTOR3(SCREEN_WIDTH / 2 ,SCREEN_HEIGHT / 2, 0.0f))

enum STARS
{
	TOP,
	MIDDLE_LEFT,
	LOWER_LEFT,
	LOWER_RIGHT,
	MIDDLE_RIGHT,
	CENTER
};

#include "GameSceneUIManager.h"
#include "UIdrawer.h"

class Object;

/**************************************
�O���錾
***************************************/
class GameSceneUI;
class Cursor;

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
class Star :public Object
{
public:
	Star * star[STAR_MAX];
	Cursor*cursor;
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	void RotateStar(int num);
	void ToggleRotateStar(int num, bool isRotated);
	bool IsStarSelected(int num);
};

void GetStarPosition(D3DXVECTOR3 *pos);

#endif

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

#define COLLIDERSIZE_STAR			(D3DXVECTOR3(120.0f,120.0f,0.0f))

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

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitStar	(void);
void	UninitStar	(void);
void	UpdateStar	(void);
void	DrawStar	(void);
void	ToggleRotateStar(int num, bool isRotated);
bool	IsStarSelected(int num);
void	GetStarPosition(D3DXVECTOR3 *pos);

#endif

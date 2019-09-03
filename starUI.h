//=============================================================================
//
// �X�^�[��ʏ��� [star.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _STAR_H_
#define _STAR_H_

#include <vector>

//*****************************************************************************
// �}�N����`
//*****************************************************************************
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

/**************************************
�O���錾
***************************************/
class RotateObject;

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
class Star
{
public:
	Star();
	~Star();

	void Update(HWND hWnd);
	void Draw(void);

	void ToggleRotateStar(int num, bool isRotated);
	void GetStarPosition(std::vector<D3DXVECTOR3>& out);

private:
	RotateObject * star[STAR_MAX];
	void RotateStar(int num);
};

#endif

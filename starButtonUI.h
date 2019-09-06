//=============================================================================
//
// �X�^�[��ʏ��� [starButtonUI.h]
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
class StarButton
{
public:
	StarButton();
	~StarButton();

	void Update(HWND hWnd);
	void Draw(void);

	void ToggleRotateStar(int num, bool isRotated);
	void GetStarButtonPosition(std::vector<D3DXVECTOR3>& out);

private:
	RotateObject * star[STAR_MAX];
	RotateObject * outerCircle[STAR_MAX];
	RotateObject * innerCircle[STAR_MAX];	

	void RotateStar(int num);
	void RotateCircle(void);
};

#endif

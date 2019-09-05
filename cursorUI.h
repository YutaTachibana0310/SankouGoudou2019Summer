//=============================================================================
//
// �J�[�\����ʏ��� [cursor.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _CURSOR_H_
#define _CURSOR_H_

/**************************************
�O���錾
***************************************/
class RotateObject;
class GameSceneUIManager;

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
class Cursor
{
public:
	Cursor();
	~Cursor();

	void PaintCursorRed();
	void PaintCursorYellow();
	void Update(HWND hWnd);
	void Draw(void);
	bool IsCursorOvered(D3DXVECTOR3 pos, D3DXVECTOR3 size);

private:
	RotateObject * innerCircle;
	RotateObject * outerCircle;
};

#endif

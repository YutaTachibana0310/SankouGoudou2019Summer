//=====================================
//
//�Q�[���w�b�_[Game.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/

//�V�[����`
enum Scene{		
	SceneTitle,
	SceneGame,
	SceneResult,
	SceneMax
};

/**************************************
�v���g�^�C�v�錾
***************************************/
void InitGame(HINSTANCE hInstance, HWND hWnd);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);

void ChangeScene(Scene next);
LPDIRECT3DTEXTURE9 GetDrawDataTemp();
#endif
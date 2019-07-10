//=====================================
//
//ゲームヘッダ[Game.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/

//シーン定義
enum Scene{		
	SceneTitle,
	SceneGame,
	SceneResult,
	SceneEditor,
	SceneMax
};

/**************************************
プロトタイプ宣言
***************************************/
void InitGame(HINSTANCE hInstance, HWND hWnd);
void UninitGame(void);
void UpdateGame(HWND hWnd);
void DrawGame(void);

void ChangeScene(Scene next);
void MaskRun(Scene next);
LPDIRECT3DTEXTURE9 GetDrawDataTemp();
#endif
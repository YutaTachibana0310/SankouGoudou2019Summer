//=====================================
//
//ボム処理[Bomb.cpp]
//Author:GP12B332 12 権頭啓太
//
//=====================================
#include "main.h"
#include "Bomb.h"
#include "player.h"
/**************************************
マクロ定義
***************************************/

#define POS0	D3DXVECTOR3(-90.0f,-10.0, -200.0f)
#define POS1	D3DXVECTOR3(-10.0f,-30.0, -200.0f)
#define POS2	D3DXVECTOR3(-100.0f,-50.0, -200.0f)
#define POS3	D3DXVECTOR3(90.0f,10.0, -200.0f)
#define POS4	D3DXVECTOR3(0.0f,30.0, -200.0f)
#define POS5	D3DXVECTOR3(50.0f,-10.0, -200.0f)
#define POS6	D3DXVECTOR3(100.0f,-10.0, -200.0f)


#define BOMB_ACCELERATION_MAX	(500.0f)
/**************************************
構造体定義
***************************************/
enum POS
{
	pos0,
	pos1,
	pos2,
	pos3,
	pos4,
	pos5,
	pos6,

};

/**************************************
グローバル変数
***************************************/


/**************************************
プロトタイプ宣言
***************************************/
void CalcBomb(Bomb *ptr);
/***************************************
* 初期化処理
****************************************/
HRESULT InitBomb(void)
{

}

/**************************************
終了処理
***************************************/
void UninitBomb(void)
{

}

/**************************************
更新処理
***************************************/
void UpdateBomb(void)
{

}

/**************************************
描画処理
***************************************/
void DrawBomb(void)
{

}

/**************************************
*ボムのセット
***************************************/
bool SetBomb(void)
{

	return true;
	//booooooooooooooooooooooomb
}
///***************************************
//加速度の計算処理
//****************************************/
//void CalcBomb(Bomb *ptr)
//{
//	if (ptr->cntFrame <= 0)
//	{
//		return;
//	}
//
//	float time = ptr->cntFrame / 60.0f;
//
//	//D3DXVECTOR3 diff = player.pos - pos0;
//
//	D3DXVECTOR3 acceleration = (diff - ptr->velocity * time) * 2.0f / (time * time);
//	if (D3DXVec3LengthSq(&acceleration) > powf(BOMB_ACCELERATION_MAX, 2))
//	{
//		D3DXVec3Normalize(&acceleration, &acceleration);
//		acceleration = acceleration * BOMB_ACCELERATION_MAX;
//	}
//
//	ptr->velocity += acceleration / 60.0f;
//
//	ptr->cntFrame--;
//};

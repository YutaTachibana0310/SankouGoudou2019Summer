//=====================================
//
//ベースエミッタ処理[BaseEmitter.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "BaseEmitter.h"

/**************************************
マクロ定義
***************************************/

/**************************************
構造体定義
***************************************/

/**************************************
グローバル変数
***************************************/

/**************************************
コンストラクタ
***************************************/
BaseEmitter::BaseEmitter(D3DXVECTOR3 *pos)
{
	this->transform.pos = *pos;
	active = true;
}

/**************************************
デストラクタ
***************************************/
BaseEmitter::~BaseEmitter()
{

}
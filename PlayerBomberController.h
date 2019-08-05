//======================================
//
//プレイヤーボンバーコントローラヘッダ[PlayerBomberController.h]
//Autthor: 権頭
//
//======================================
#ifndef _PLAYERBOMBERCONTROLLER_H_
#define _PLAYERBOMBERCONTROLLER_H_

#include "main.h"
#include "PlayerBomber.h"
#include <vector>

/***********************************
マクロ定義
************************************/

/*************************************
PlayerBomberControllerクラス
PlayerBomberを管理
**************************************/
class PlayerBomberController
{
public:
	PlayerBomberController();
	~PlayerBomberController();

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SetPlayerBomber(std::vector<D3DXVECTOR3>targetList, D3DXVECTOR3 initpos);

	LPDIRECT3DVERTEXBUFFER9 vtxBuff;
	//可変長配列
	std::vector<PlayerBomber*> bomberContainer;
	LPDIRECT3DTEXTURE9 texture;

};




#endif
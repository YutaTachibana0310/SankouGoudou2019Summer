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
#include <list>

class Enemy;
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

	void SetPlayerBomber(std::list<Enemy*>targetList, D3DXVECTOR3 initpos);

	bool CanStock();
	bool CanSet();
	void AddStock();

	LPDIRECT3DVERTEXBUFFER9 vtxBuff;
	//可変長配列
	std::vector<PlayerBomber*> bomberContainer;
	LPDIRECT3DTEXTURE9 texture;
	
private:
	int stockInterval;
	int stock;
};




#endif
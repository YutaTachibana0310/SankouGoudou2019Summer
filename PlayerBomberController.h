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
#include <memory>

/***********************************
前方宣言
************************************/
class Enemy;
class BossEnemyModel;
class RebarObstacle;

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

	void SetPlayerBomber(std::list<std::shared_ptr<Enemy>>& targetList, D3DXVECTOR3 initpos);
	void SetPlayerBomber(std::shared_ptr<BossEnemyModel> targett, D3DXVECTOR3 initPos);
	void SetPlayerBomber(std::list<std::shared_ptr<RebarObstacle>>& targetList, D3DXVECTOR3 initPos);

	bool CanStock();
	bool CanSet();
	void AddStock();

	LPDIRECT3DVERTEXBUFFER9 vtxBuff;
	LPDIRECT3DTEXTURE9 texture;
	std::list<std::unique_ptr<PlayerBomber>> bomberContainer;

private:
	int stockInterval;
	int stock;
};




#endif
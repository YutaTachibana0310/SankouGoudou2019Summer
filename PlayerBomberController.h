//======================================
//
//�v���C���[�{���o�[�R���g���[���w�b�_[PlayerBomberController.h]
//Autthor: ����
//
//======================================
#ifndef _PLAYERBOMBERCONTROLLER_H_
#define _PLAYERBOMBERCONTROLLER_H_

#include "main.h"
#include "PlayerBomber.h"
#include <vector>
#include <list>
#include <memory>

class Enemy;
/***********************************
�O���錾
************************************/
class PlayerBomberEnemy;

/*************************************
PlayerBomberController�N���X
PlayerBomber���Ǘ�
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
	void SetPlayerBomber(std::list<std::shared_ptr<Transform>>& targetList, D3DXVECTOR3 initPos);

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
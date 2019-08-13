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

class Enemy;
/***********************************
�}�N����`
************************************/

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

	void SetPlayerBomber(std::list<Enemy*>targetList, D3DXVECTOR3 initpos);

	bool CanStock();
	bool CanSet();
	void AddStock();

	LPDIRECT3DVERTEXBUFFER9 vtxBuff;
	//�ϒ��z��
	std::vector<PlayerBomber*> bomberContainer;
	LPDIRECT3DTEXTURE9 texture;
	
private:
	int stockInterval;
	int stock;
};




#endif
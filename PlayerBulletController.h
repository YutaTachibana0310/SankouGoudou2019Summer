//=====================================
//
//�v���C���[�o���b�g�R���g���[���w�b�_[PlayerBulletController.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _PLAYERBULLETCONTROLLER_H_
#define _PLAYERBULLETCONTROLLER_H_

#include "main.h"
#include "LineTrailModel.h"
#include "PlayerBullet.h"
#include <vector>

/**************************************
�}�N����`
***************************************/

/**************************************
PlayerBulletController�N���X
PlayerBullet���Ǘ�����
***************************************/
class PlayerBulletController
{
public:
	PlayerBulletController();
	~PlayerBulletController();

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SetPlayerBullet(LineTrailModel model);

private:
	std::vector<PlayerBullet*> bulletContainer;
	LPDIRECT3DTEXTURE9 texture;
};

#endif
//=====================================
//
//�{�X�R���g���[���w�b�_[BossController.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _BOSSCONTROLLER_H_
#define _BOSSCONTROLLER_H_

#include "main.h"
#include "BossEnemyModel.h"
#include "EnemyBulletController.h"

/**************************************
�O���錾
***************************************/

/**************************************
�}�N���E�񋓎q��`
***************************************/

/**************************************
�N���X��`
***************************************/
class BossController
{
public:
	BossController(const Transform& player);
	~BossController();

	void Update();
	void Draw();

	void SetActive(bool state);

private:
	bool active;
	BossEnemyModel *bossModel;
};

#endif
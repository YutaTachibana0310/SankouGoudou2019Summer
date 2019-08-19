//=====================================
//
//�{�X�R���C�_�[�R���g���[���w�b�_[BossColliderController.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _BOSSCOLLIDERCONTROLLER_H_
#define _BOSSCOLLIDERCONTROLLER_H_

#include "main.h"
#include "TrailCollider.h"

#include <list>
#include <vector>

/**************************************
�O���錾
***************************************/
class BossColliderGuide;

/**************************************
�}�N���E�񋓎q��`
***************************************/

/**************************************
�N���X��`
***************************************/
class BossColliderController
{
public:
	BossColliderController();
	~BossColliderController();

	void Update();
	void Draw();

	void SetCollider(const std::vector<int>& edgeList);
	void DeleteAll();

private:
	std::list<BossColliderGuide*> guideList;
	std::list<TrailCollider*> colliderList;

	float posZ;
};

#endif
//=====================================
//
//�{�XUI�}�l�[�W���w�b�_[BossUIManager.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _BOSSUIMANAGER_H_
#define _BOSSUIMANAGER_H_

#include "main.h"
#include <vector>

/**************************************
�O���錾
***************************************/
class WarningUI;
class BossBulletGuide;
class LineTrailModel;

/**************************************
�}�N���E�񋓎q��`
***************************************/

/**************************************
�N���X��`
***************************************/
class BossUImanager
{
public:
	BossUImanager();
	~BossUImanager();

	void Update();
	void Draw();

	void SetWarning();
	void SetBulletGuide(LineTrailModel& model);

private:
	WarningUI *warning;
	std::vector<BossBulletGuide*> bulletGuide;
};

#endif
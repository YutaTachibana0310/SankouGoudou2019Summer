//=====================================
//
//�{�XUI�}�l�[�W���w�b�_[BossUIManager.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _BOSSUIMANAGER_H_
#define _BOSSUIMANAGER_H_

#include "main.h"

/**************************************
�O���錾
***************************************/
class WarningUI;

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

private:
	WarningUI *warning;
};

#endif